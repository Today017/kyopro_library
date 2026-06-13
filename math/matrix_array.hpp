#pragma once
#include"../../kyopro_library/template.hpp"

template<typename Ring, int N>
array<array<typename Ring::Type,N>,N> MatMul(
    const array<array<typename Ring::Type,N>,N>& A,
    const array<array<typename Ring::Type,N>,N>& B
) {
    using Type=typename Ring::Type;
    array<array<Type,N>,N> ret;
    rep(i,N) rep(j,N) ret[i][j]=Ring::zero();
    rep(i,N) rep(j,N) rep(k,N) ret[i][j]=Ring::plus(ret[i][j],Ring::mul(A[i][k],B[k][j]));
    return ret;
}

template<typename Ring, int N>
array<array<typename Ring::Type,N>,N> MatPow(
    array<array<typename Ring::Type,N>,N> A,
    ll b
) {
    using Type=typename Ring::Type;
    array<array<Type,N>,N> ret;
    rep(i,N) rep(j,N) ret[i][j]=Ring::zero();
    rep(i,N) ret[i][i]=Ring::one();
    while(b) {
        if(b&1) ret=MatMul<Ring,N>(ret,A);
        A=MatMul<Ring,N>(A,A);
        b>>=1;
    }
    return ret;
}
