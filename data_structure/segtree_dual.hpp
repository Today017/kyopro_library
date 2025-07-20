#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 双対セグメント木
/// @tparam CommutativeOperator 作用素
/// @attention 作用素は果敢である必要がある
template<typename CommutativeOperator>
struct SegTreeDual {
    using Type=typename CommutativeOperator::Type;
    SegTreeDual()=default;

    /// @brief 要素数 n の双対セグ木を構築する
    SegTreeDual(int n) {
        this->n=n;
        dat=vector<Type>(n<<1,CommutativeOperator::id());
    }

    /// @brief 配列 v から双対セグ木を構築する
    SegTreeDual(const vector<Type>& v) {
        this->n=v.size();
        dat=vector<Type>(n<<1,CommutativeOperator::id());
        for(int i=0; i<n; i++) dat[i+n]=v[i];
        for(int i=n-1; i>0; i--) dat[i]=CommutativeOperator::op(dat[i<<1],dat[i<<1|1]);
    }

    void apply(int l, int r, Type x) {
        l+=n; r+=n;
        while(l<r) {
            if(l&1) dat[l]=CommutativeOperator::op(dat[l],x), l++;
            if(r&1) r--, dat[r]=CommutativeOperator::op(dat[r],x);
            l>>=1; r>>=1;
        }
    }
    Type get(int i) {
        i+=n;
        Type ret=CommutativeOperator::id();
        while(i) {
            ret=CommutativeOperator::op(ret,dat[i]);
            i>>=1;
        }
        return ret;
    }

    int size() { return n; }
    Type operator[](int i) { return get(i); }

private:
    int n;
    vector<Type> dat;
};

#include"../../kyopro_library/others/operator.hpp"

namespace RangeQuery {
    template<typename T>
    struct ApplyAdd { using Type=struct SegTreeDual<Operator::Add<T>>; };

    template<typename T>
    struct ApplyUpdate { using Type=struct SegTreeDual<Operator::UpdateTimeStamp<T>>; };
}