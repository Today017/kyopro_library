#include"../../kyopro_library/template.hpp"

template<typename T>
vector<vector<T>> MatMul(const vector<vector<T>>& A, const vector<vector<T>>& B) {
    int N=A.size();
    vector<vector<T>> ret(N,vector<T>(N));
    REP(i,N) REP(j,N) REP(k,N) ret[i][j]+=A[i][k]*B[k][j];
    return ret;
}

template<typename T>
vector<vector<T>> MatPow(vector<vector<T>> A, ll b) {
    int N=A.size();
    vector<vector<T>> ret(N,vector<T>(N));
    REP(i,N) ret[i][j]=1;
    while(b) {
        if(b&1) ret=MatMul(ret,A);
        A=MatMul(A,A);
        b>>=1;
    }
    return ret;
}