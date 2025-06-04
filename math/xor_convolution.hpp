#include "../../kyopro_library/template.hpp"

/// @brief 高速アダマール変換
template<typename T>
void FHT(vector<T>& a, bool inv=false) {
    int h=__lg(a.size());
    REP(i,h) REP(j,1<<h) if(~j>>i&1) {
        T x=a[j],y=a[j|1<<i];
        a[j]=x+y,a[j|1<<i]=x-y;
        if(inv) a[j]/=2,a[j|1<<i]/=2;
    }
    return;
}

/// @brief XOR Convolution
/// @brief C[k] = Σ(i^j = k) A[i]B[j] なる C を返す
/// @note O(n log(n))
template<typename T>
vector<T> XorConvolution(vector<T> a, vector<T> b) {
    FHT(a); FHT(b);
    REP(i,a.size()) a[i]*=b[i];
    FHT(a,true);
    return a;
}
