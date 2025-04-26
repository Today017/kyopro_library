#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief セグメント木
template<typename Monoid>
struct SegTree {
    using Type=typename Monoid::Type;
    SegTree()=default;

    /// @brief 要素数 n のセグ木を構築する
    SegTree(int n) {
        this->n=n;
        dat.assign(n<<1,Monoid::id());
        cand.reserve(100),cand_l.reserve(100),cand_r.reserve(100);
    }

    /// @brief 配列 v からセグ木を構築する
    /// @note O(N)
    SegTree(const vector<Type>& v) {
        this->n=v.size();
        dat.assign(n<<1,Monoid::id());
        for(int i=0; i<n; i++) dat[i+n]=v[i];
        for(int i=n-1; i>0; i--) dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
        cand.reserve(100),cand_l.reserve(100),cand_r.reserve(100);
    }

    /// @brief i 番目の要素を x に変更する
    /// @note O(log(N))
    void set(int i, Type x) {
        i+=n;
        dat[i]=x;
        while(i>>=1) dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
    }

    /// @brief 区間 [l, r) のモノイド積を返す
    /// @note O(log(N))
    Type fold(int l, int r) {
        Type retl=Monoid::id(),retr=Monoid::id();
        l+=n,r+=n;
        while(l<r) {
            if(l&1) retl=Monoid::op(retl,dat[l++]);
            if(r&1) retr=Monoid::op(dat[--r],retr);
            l>>=1,r>>=1;
        }
        return Monoid::op(retl,retr);
    }

    /// @brief 区間 [l, x) のモノイド積が f を満たすような最大の x >= l を返す
    /// @attention `f(Monoid::id())=true` が成り立つ必要がある
    /// @note O(log(N))
    template<typename F>
    int find_right(int l, F f) {
        assert(f(Monoid::id()));
        if(l==n) return n;
        l+=n;
        int r=n+n;
        cand_l.clear(),cand_r.clear();
        while(l<r) {
            if(l&1) cand_l.push_back(l++);
            if(r&1) cand_r.push_back(--r);
            l>>=1,r>>=1;
        }
        cand=cand_l;
        reverse(cand_r.begin(),cand_r.end());
        cand.insert(cand.end(),cand_r.begin(),cand_r.end());
        Type val=Monoid::id();
        for(int i:cand) {
            if(f(Monoid::op(val,dat[i]))) {
                val=Monoid::op(val,dat[i]);
            } else {
                while(i<n) {
                    i<<=1;
                    if(f(Monoid::op(val,dat[i]))) {
                        val=Monoid::op(val,dat[i]);
                        i|=1;
                    }
                }
                return i-n;
            }
        }
        return n;
    }

    /// @brief 区間 [x, r) のモノイド積が f を満たすような最小の x <= r を返す
    /// @attention `f(Monoid::id())=true` が成り立つ必要がある
    /// @note O(log(N))
    template<typename F>
    int find_left(int r,F f) {
        assert(f(Monoid::id()));
        if(r==0) return 0;
        r+=n;
        int l=n;
        cand_l.clear(),cand_r.clear();
        while(l<r) {
            if(l&1) cand_l.push_back(l++);
            if(r&1) cand_r.push_back(--r);
            l>>=1,r>>=1;
        }
        cand=cand_r;
        reverse(cand_l.begin(),cand_l.end());
        cand.insert(cand.end(),cand_l.begin(),cand_l.end());
        Type val=Monoid::id();
        for(int i:cand) {
            if(f(Monoid::op(dat[i],val))) {
                val=Monoid::op(dat[i],val);
            } else {
                while(i<n) {
                    i=(i<<1)|1;
                    if(f(Monoid::op(dat[i],val))) {
                        val=Monoid::op(dat[i],val);
                        i^=1;
                    }
                }
                return i-n+1;
            }
        }
        return 0;
    }

    /// @brief i 番目の要素を返す
    /// @note O(1)
    Type operator[](int i) { return dat[i+n]; }

    /// @brief 配列のサイズを返す
    int size() { return n; }

private:
    int n;
    vector<Type> dat;
    vector<int> cand,cand_l,cand_r;
};

#include"../../kyopro_library/others/monoid.hpp"

/// @brief 区間クエリ
namespace RangeQuery {
    /// @brief 1点変更 / 区間 min
    template<typename T, T max_value=INF>
    struct Min { using Type=struct SegTree<Monoid::Min<T,max_value>>; };

    /// @brief 1点変更 / 区間 max
    template<typename T, T min_value=-INF>
    struct Max { using Type=struct SegTree<Monoid::Max<T,min_value>>; };

    /// @brief 1点変更 / 区間和
    template<typename T>
    struct Sum { using Type=struct SegTree<Monoid::Sum<T>>; };
}
