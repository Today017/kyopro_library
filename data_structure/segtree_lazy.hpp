#pragma once
#include"../../kyopro_library/template.hpp"

///@brief 遅延評価セグメント木
///@tparam Monoid モノイド
///@tparam Operator 作用素
///@tparam mapping （モノイドの元，作用素の元）→モノイドの元を返す関数
template<typename Monoid, typename Operator, auto mapping>
struct SegTreeLazy {
    using MonoidType=typename Monoid::Type;
    using OperatorType=typename Operator::Type;
    SegTreeLazy()=default;

    ///@brief 要素数 n の遅延セグ木を構築する
    SegTreeLazy(int n) {
        this->n=n;
        dat=vector<MonoidType>(n<<1,Monoid::id());
        lazy=vector<OperatorType>(n<<1,Operator::id());
        indices.reserve(100); cand.reserve(100); cand_l.reserve(100); cand_r.reserve(100);
    }

    ///@brief 配列 v から遅延セグ木を構築する
    SegTreeLazy(const vector<MonoidType>& v) {
        this->n=v.size();
        dat=vector<MonoidType>(n<<1,Monoid::id());
        lazy=vector<OperatorType>(n<<1,Operator::id());
        rep(i,n) dat[i+n]=v[i];
        for(int i=n-1; i>0; i--) dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
        indices.reserve(100); cand.reserve(100); cand_l.reserve(100); cand_r.reserve(100);
    }

    ///@brief i 番目の要素を x に更新する
    void set(int i, MonoidType x) {
        generate_indices(i,i+1);
        pushdown();
        i+=n;
        dat[i]=x;
        while(i>>=1) dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
    }

    ///@brief 区間 [l, r) に x を作用させる
    void apply(int l, int r, OperatorType x) {
        if(l==r) return;
        generate_indices(l,r);
        pushdown();
        l+=n; r+=n;
        while(l<r) {
            if(l&1) {
                lazy[l]=Operator::op(lazy[l],x);
                dat[l]=mapping(dat[l],x);
                l++;
            }
            if(r&1) {
                r--;
                lazy[r]=Operator::op(lazy[r],x);
                dat[r]=mapping(dat[r],x);
            }
            l>>=1; r>>=1;
        }
        pushup();
    }

    ///@brief 区間 [l, r) のモノイド積を返す
    MonoidType fold(int l, int r) {
        if(l==r) return Monoid::id();
        generate_indices(l,r);
        pushdown();
        MonoidType retl=Monoid::id(),retr=Monoid::id();
        l+=n; r+=n;
        while(l<r) {
            if(l&1) retl=Monoid::op(retl,dat[l++]);
            if(r&1) retr=Monoid::op(dat[--r],retr);
            l>>=1; r>>=1;
        }
        return Monoid::op(retl,retr);
    }

    ///@brief 区間 [l, x) のモノイド積が f を満たすような最大の x >= l を返す
    ///@attention `f(Monoid::id())=true` が成り立つ必要がある
    ///@note O(log(N))
    template<typename F>
    int find_right(int l, F f) {
        assert(f(Monoid::id()));
        if(l==n) return n;
        generate_indices(l,n);
        pushdown();
        l+=n;
        int r=n+n;
        cand_l.clear(); cand_r.clear();
        while(l<r) {
            if(l&1) cand_l.push_back(l++);
            if(r&1) cand_r.push_back(--r);
            l>>=1; r>>=1;
        }
        cand=cand_l;
        reverse(all(cand_r));
        cand.insert(cand.end(),all(cand_r));
        MonoidType val=Monoid::id();
        for(int i:cand) {
            if(f(Monoid::op(val,dat[i]))) {
                val=Monoid::op(val,dat[i]);
            } else {
                while(i<n) {
                    propagate(i);
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

    ///@brief 区間 [x, r) のモノイド積が f を満たすような最小の x<=r を返す
    ///@attention `f(Monoid::id())=true` が成り立つ必要がある
    ///@note O(log(N))
    template<typename F>
    int find_left(int r, F f) {
        assert(f(Monoid::id()));
        if(r==0) return 0;
        generate_indices(0,r);
        pushdown();
        r+=n;
        int l=n;
        cand_l.clear(); cand_r.clear();
        while(l<r) {
            if(l&1) cand_l.push_back(l++);
            if(r&1) cand_r.push_back(--r);
            l>>=1; r>>=1;
        }
        cand=cand_r;
        reverse(all(cand_l));
        cand.insert(cand.end(),all(cand_l));
        MonoidType val=Monoid::id();
        for(int i:cand) {
            if(f(Monoid::op(dat[i],val))) {
                val=Monoid::op(dat[i],val);
            } else {
                while(i<n) {
                    propagate(i);
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

    int size() { return n; }
    MonoidType operator[](int i) { return fold(i,i+1); }

private:
    int n;
    vector<MonoidType> dat;
    vector<OperatorType> lazy;
    vector<int> indices, cand, cand_l, cand_r;
    void generate_indices(int l, int r) {
        indices.clear();
        l+=n; r+=n;
        int lm=(l/(l&-l))>>1,rm=(r/(r&-r))>>1;
        while(l<r) {
            if(l<=lm) indices.push_back(l);
            if(r<=rm) indices.push_back(r);
            l>>=1; r>>=1;
        }
        while(l) {
            indices.push_back(l);
            l>>=1;
        }
    }
    void propagate(int i) {
        if(i<n) {
            lazy[i<<1]=Operator::op(lazy[i<<1],lazy[i]);
            lazy[i<<1|1]=Operator::op(lazy[i<<1|1],lazy[i]);
            dat[i<<1]=mapping(dat[i<<1],lazy[i]);
            dat[i<<1|1]=mapping(dat[i<<1|1],lazy[i]);
        }
        lazy[i]=Operator::id();
    }
    void pushdown() {
        for(int j=(int)indices.size()-1; j>=0; j--) {
            int i=indices[j];
            propagate(i);
        }
    }
    void pushup() {
        rep(j,(int)indices.size()) {
            int i=indices[j];
            dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
        }
    }
};

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/operator.hpp"

namespace RangeQuery {
    ///@brief 区間更新 / 区間min
    ///@tparam max_value 最大値
    ///@tparam not_exist 存在しない値
    template<typename T, T max_value, T not_exist>
    struct ApplyUpdate_GetMin {
        static T mapping(const T& a, const T& b) { return b==not_exist?a:b; }
        using Type=struct SegTreeLazy<Monoid::Min<T,max_value>,Operator::Update<T,not_exist>,mapping>;
    };

    ///@brief 区間更新 / 区間max
    ///@tparam min_value 最小値
    ///@tparam not_exist 存在しない値
    template<typename T, T min_value, T not_exist>
    struct ApplyUpdate_GetMax {
        static T mapping(const T& a, const T& b) { return b==not_exist?a:b; }
        using Type=struct SegTreeLazy<Monoid::Max<T,min_value>,Operator::Update<T,not_exist>,mapping>;
    };

    ///@brief 区間更新 / 区間和
    ///@tparam not_exist 存在しない値
    template<typename T, T not_exist>
    struct ApplyUpdate_GetSum {
        using S=typename Monoid::SumPair<T>::Type;
        static S mapping(const S& a, const T& b) { return b==not_exist?a:S{b*a.second,a.second}; }
        using Type=struct SegTreeLazy<Monoid::SumPair<T>,Operator::Update<T,not_exist>,mapping>;
    };

    ///@brief 区間加算 / 区間min
    template<typename T, T max_value>
    struct ApplyAdd_GetMin {
        static T mapping(const T& a, const T& b) { return a+b; }
        using Type=struct SegTreeLazy<Monoid::Min<T,max_value>,Operator::Add<T>,mapping>;
    };

    ///@brief 区間加算 / 区間max
    template<typename T, T min_value>
    struct ApplyAdd_GetMax {
        static T mapping(const T& a, const T& b) { return a+b; }
        using Type=struct SegTreeLazy<Monoid::Max<T,min_value>,Operator::Add<T>,mapping>;
    };

    ///@brief 区間加算 / 区間和
    template<typename T>
    struct ApplyAdd_GetSum {
        using S=typename Monoid::SumPair<T>::Type;
        static S mapping(const S& a, const T& b) { return {a.first+b*a.second,a.second}; }
        using Type=struct SegTreeLazy<Monoid::SumPair<T>,Operator::Add<T>,mapping>;
    };
}