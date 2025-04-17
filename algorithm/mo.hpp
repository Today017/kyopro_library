#include"../../kyopro_library/template.hpp"

/// @brief Mo's Algorithm
/// @ref https://ei1333.hateblo.jp/entry/2017/09/11/211011
template<ll L=20>
struct Mo{
    /// @brief コンストラクタ
    Mo(int n){
        this->n=n;
        max_n=1<<L;
    }

    /// @brief クエリ [l, r) を追加する
    void add(int l, int r){
        q++;
        ls.push_back(l);
        rs.push_back(r);
    }

    /// @brief  クエリを実行する
    /// @param add_left `add_left(i)` i 番目の要素が左から加わるときの処理
    /// @param add_right `add_right(i)` i 番目の要素が右から加わるときの処理
    /// @param del_left `del_left(i)` i 番目の要素が左から抜けるときの処理
    /// @param del_right `del_right(i)` i 番目の要素が右から抜けるときの処理
    /// @param out `out(i)` i 番目のクエリの答えを求めたときの処理
    /// @note O(N sqrt(Q))
    template<typename F1, typename F2, typename F3, typename F4, typename F5>
    void execute(F1&& add_left, F2&& add_right, F3&& del_left, F4&& del_right, F5&& out){
        VI qi(q); iota(ALL(qi),0);
        VL eval(q);
        REP(i,q) eval[i]=hilbertorder(ls[i],rs[i]);
        sort(ALL(qi),[&](int i, int j){ return eval[i]<eval[j]; });
        int nl=0,nr=0;
        for(int& i:qi){
            while(nl>ls[i]) add_left(--nl);
            while(nr<rs[i]) add_right(nr++);
            while(nl<ls[i]) del_left(nl++);
            while(nr>rs[i]) del_right(--nr);
            out(i);
        }
    }

private:
    int n,q;
    ll max_n;
    VI ls,rs;
    ll hilbertorder(int x, int y){
        ll rx,ry,d=0;
        for(ll s=max_n>>1ll; s; s>>=1ll){
            rx=(x&s)>0,ry=(y&s)>0;
            d+=s*s*((rx*3)^ry);
            if(ry) continue;
            if(rx) x=max_n-1-x,y=max_n-1-y;
            swap(x,y);
        }
        return d;
    }
};