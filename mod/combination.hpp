#include"../../kyopro_library/template.hpp"

/// @brief 二項係数・階乗計算
template<typename T>
struct Combinatorics {
    Combinatorics()=default;

    /// @brief 二項係数の前計算
    /// @note O(N)
    Combinatorics(int n) {
        fac=vector<T>(n+1);
        finv=vector<T>(n+1);
        fac[0]=1;
        for(int i=1; i<=n; i++) fac[i]=fac[i-1]*i;
        finv[n]=fac[n].inv();
        for(int i=n; i>=1; i--) finv[i-1]=finv[i]*i;
    }

    /// @brief nCr を返す
    /// @note n < 0, r < 0, n < r のときは 0 を返す
    T comb(ll n, ll r) {
        if(n<0 || r<0 || n-r<0) return 0;
        return fac[n]*finv[r]*finv[n-r];
    }

    /// @brief nPr を返す
    /// @note n < 0, r < 0, n < r のときは 0 を返す
    T perm(ll n, ll r) {
        if(n<0 || r<0 || n-r<0) return 0;
        return fac[n]*finv[n-r];
    }

    /// @brief n! を返す
    T factrial(int n) { return fac[n]; }

    /// @brief (n!)^-1 を返す
    T factinv(int n) { return finv[n]; }

    /// @brief nCr を返す
    T operator()(ll n, ll r) { return comb(n,r); }

private:
    vector<T> fac,finv;
};