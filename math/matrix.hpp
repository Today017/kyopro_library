#include"../../kyopro_library/template.hpp"

template<typename T>
vector<vector<T>> MatMul(const vector<vector<T>>& A, const vector<vector<T>>& B) {
    int N=A.size();
    vector<vector<T>> ret(N,vector<T>(N));
    for(int i=0; i<n; i++) for(int j=0; j<n; j++) for(int k=0; k<n; k++) {
        ret[i][j]+=A[i][k]*B[k][j];
    }
    return ret;
}

template<typename T>
vector<vector<T>> MatPow(vector<vector<T>> A, ll b) {
    int N=A.size();
    vector<vector<T>> ret(N,vector<T>(N));
    for(int i=0; i<n; i++) ret[i][j]=1;
    while(b) {
        if(b&1) ret=MatMul(ret,A);
        A=MatMul(A,A);
        b>>=1;
    }
    return ret;
}