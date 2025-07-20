#include"../../kyopro_library/template.hpp"

/// @brief 更新 O(1) クエリ O(sqrt(N)) の改造版セグ木
/// @brief Mo's Algorithmとの相性が良い
/// @note モノイドではなくアーベル群が乗る（モノイドや群の場合、更新が Θ(√N) でメリットがない）
/// @ref https://atcoder.jp/contests/abc405/submissions/65704867
template<typename Abel>
struct SqrtTree {
    using Type=typename Abel::Type;
    SqrtTree()=default;

    SqrtTree(int n) {
        this->n=n;
        rn=1;
        while(rn*rn<n) rn++;
        dat=vector<Type>(n,Abel::id());
        dat2=vector<Type>(n,Abel::id());
        dat2_inv=vector<Type>(n,Abel::id());
    }

    /// @brief 配列 v で初期化する
    SqrtTree(const vector<Type>& v) {
        this->n=v.size();
        rn=1;
        while(rn*rn<n) rn++;
        dat.assign(rn,Abel::id());
        dat2=v;
        for(int i=0; i<rn; i++) {
            for(int j=i*rn; j<min((i+1)*rn,n); j++) {
                dat[i]=Abel::op(dat[i],dat2[j]);
                dat2_inv[j]=Abel::inv(dat2[j]);
            }
        }
    }

    /// @brief 配列 v とその逆元 v_inv で初期化する
    SqrtTree(const vector<Type>& v, const vector<Type>& v_inv) {
        this->n=v.size();
        rn=1;
        while(rn*rn<n) rn++;
        dat.assign(rn,Abel::id());
        dat2=v;
        dat2_inv=v_inv;
        for(int i=0; i<rn; i++) {
            for(int j=i*rn; j<min((i+1)*rn,n); j++) {
                dat[i]=Abel::op(dat[i],dat2[j]);
            }
        }
    }

    /// @brief i 番目の要素を x に更新する
    /// @note O(f) （f : 逆元を求めるのにかかる計算量）
    void set(int i, Type x) {
        int j=i/rn;
        dat[j]=Abel::op(dat[j],Abel::inv(dat2[i]));
        dat2[i]=x;
        dat[j]=Abel::op(dat[j],dat2[i]);
        dat2_inv[i]=Abel::inv(dat2[i]);
    }

    /// @brief i 番目の要素を x に更新し、その逆元を x_inv に更新する
    void set(int i, Type x, Type x_inv) {
        int j=i/rn;
        dat[j]=Abel::op(dat[j],dat2_inv[i]);
        dat2[i]=x;
        dat2_inv[i]=x_inv;
        dat[j]=Abel::op(dat[j],dat2[i]);
    }

    /// @brief 区間 [l, r) の群積を返す
    /// @note O(√N)
    Type fold(int l, int r) {
        Type ret=Abel::id();
        while(l<r) {
            if(l%rn==0 && l+rn<=r) {
                ret=Abel::op(ret,dat[l/rn]);
                l+=rn;
            } else {
                ret=Abel::op(ret,dat2[l]);
                l++;
            }
        }
        return ret;
    }

    Type operator[](int i) const { return dat2[i]; }
    int size() const { return n; }

private:
    int n,rn;
    vector<Type> dat,dat2,dat2_inv;
};
