#include"../../kyopro_library/template.hpp"

///@brief Floor Sum
///@brief sum[i=0~N-1] floor((Ai+B) / M) を求める
///@note O(log M)時間
template<typename T=ll>
T FloorSum(T N, T M, T A, T B) {
    T ret=0;
    if(A>=M) {
        ret+=(A/M)*N*(N-1)/2;
        A%=M;
    }
    if(B>=M) {
        ret+=(B/M)*N;
        B%=M;
    }
    T Y=(A*N+B)/M;
    if(Y==0) return ret;
    T X=(M*Y-B+A-1)/A;
    ret+=(N-X)*Y+FloorSum(Y,A,M,A*X-M*Y+B);
    return ret;
}
