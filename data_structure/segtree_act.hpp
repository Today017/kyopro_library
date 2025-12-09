#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 区間作用一点取得型セグメント木
/// @tparam Operator 作用素（モノイド）
/// @ref verify: https://judge.yosupo.jp/problem/range_affine_point_get
/// @ref verify: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D
template<typename Operator>
struct SegTreeAct {
    using Type=typename Operator::Type;

    /// @brief 要素数 n で構築する
    SegTreeAct(int z) {
        n=1; while(n<z) n*=2;
        dat.resize(n*2,Operator::id());
    }

    /// @brief 配列 v から構築する
    SegTreeAct(vector<Type>& v) {
        int z=v.size();
        n=1; while(n<z) n*=2;
        dat.resize(n*2,Operator::id());
        for(int i=0; i<z; i++) dat[i+n]=v[i];
    }

    /// @brief k 番目の要素を取得する
    Type operator[](int k) {
        int i=1, l=0, r=n;
        while(i<n) {
            push(i);
            int m=(l+r)>>1;
            i<<=1;
            if(k<m) r=m;
            else l=m, i|=1;
        }
        return dat[i];
    }

    /// @brief 区間 [l, r) に x を作用させる
    void apply(int l, int r, Type x) {
        l+=n; r+=n;
        int h=__lg(n);
        for(int i=h; i>=1; i--) {
            push(l>>i);
            push((r-1)>>i);
        }
        while(l<r) {
            if(l&1) dat[l]=Operator::op(dat[l],x), l++;
            if(r&1) --r, dat[r]=Operator::op(dat[r],x);
            l>>=1; r>>=1;
        }
    }

private:
    int n;
    vector<Type> dat;

    void push(int i) {
        if(i<n) {
            dat[i<<1]=Operator::op(dat[i<<1],dat[i]);
            dat[i<<1|1]=Operator::op(dat[i<<1|1],dat[i]);
            dat[i]=Operator::id();
        }
    }
};

#include"../../kyopro_library/others/operator.hpp"

namespace RangeQuery {
    template<typename T>
    struct ApplyAdd { using Type=struct SegTreeAct<Operator::Add<T>>; };

    template<typename T, T not_exist>
    struct ApplyUpdate { using Type=struct SegTreeAct<Operator::Update<T,not_exist>>; };
}
