#include"../../kyopro_library/template.hpp"

template<typename Ring>
vector<vector<typename Ring::Type>> MatMul(
    const vector<vector<typename Ring::Type>>& A,
    const vector<vector<typename Ring::Type>>& B
) {
    using Type=typename Ring::Type;
    int N=A.size();
    vector<vector<Type>> ret(N,vector<Type>(N,Ring::zero()));
    rep(i,N) rep(j,N) rep(k,N) ret[i][j]=Ring::plus(ret[i][j],Ring::mul(A[i][k],B[k][j]));
    return ret;
}

template<typename Ring>
vector<vector<typename Ring::Type>> MatPow(
    vector<vector<typename Ring::Type>> A,
    ll b
) {
    using Type=typename Ring::Type;
    int N=A.size();
    vector<vector<Type>> ret(N,vector<Type>(N,Ring::zero()));
    rep(i,N) ret[i][i]=Ring::one();
    while(b) {
        if(b&1) ret=MatMul<Ring>(ret,A);
        A=MatMul<Ring>(A,A);
        b>>=1;
    }
    return ret;
}