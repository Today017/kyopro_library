#pragma once
#include "../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/abel.hpp"

/// @brief Fenwick Tree
/// @tparam Abel 可換群
template<typename Abel=Abel::Sum<ll>>
struct FenwickTreeAbel {
    using Type=typename Abel::Type;
    FenwickTreeAbel()=default;

    /// @brief サイズ n のFenwick Treeを構築する
    FenwickTreeAbel(int n) {
        this->n=n;
        dat=vector<Type>(n,Abel::id());
    }

    /// @brief i 番目の要素に対し v[i] <- op(v[i], x) と更新する
    /// @note O(log(N))
    void add(int i, Type x) {
        i++;
        while(i<=n) {
            dat[i-1]=Abel::op(dat[i-1],x);
            i+=i&-i;
        }
    }

    /// @brief 区間 [l, r) の群積を返す
    /// @note O(log(N))
    Type sum(int l, int r) {
        return Abel::op(Abel::inv(sum(l)),sum(r));
    }

    /// @brief i 番目の要素を返す
    /// @note O(log(N))
    Type operator[](int i) { return sum(i,i+1); }

    /// @brief 配列のサイズを返す
    int size() { return n; }

private:
    int n;
    vector<Type> dat;
    Type sum(int r) {
        Type ret=Abel::id();
        while(r>0) {
            ret=Abel::op(ret,dat[r-1]);
            r-=r&-r;
        }
        return ret;
    }
};
