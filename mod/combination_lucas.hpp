#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"

/**
 * @brief Lucas の定理を用いた二項係数計算用ライブラリ
 * @details
 * Lucas の定理
 * p を素数とし、n, r を非負整数とする。
 * また、n = n[k]p^k + n[k-1]p^(k-1) + ... + n[1]p + n[0],
 * r = r[k]p^k + r[k-1]p^(k-1) + ... + r[1]p + r[0] とする。
 * 
 * このとき、nCr(mod p) = Π[k=0~N]n[k]Cr[k]
 */
struct CombinationLucas {
    /// @brief Lucas の定理を用いて二項係数を計算するための前計算をする
    /// @note O(mod)
    CombinationLucas(int mod) {
        this->mod=mod;
        fact=vector<ll>(mod); fact[0]=1;
        factinv=vector<ll>(mod);
        for(int i=1; i<mod; i++) fact[i]=fact[i-1]*i%mod;
        factinv[mod-1]=ModInv(fact[mod-1],mod);
        for(int i=mod-2; i>=0; i--) factinv[i]=factinv[i+1]*(i+1)%mod;
    }

    /// @brief nCr mod を返す
    /// @note O(log(n))
    ll comb(int n, int r) {
        if(r==0||r==n) return 1;
        return calc(n%mod,r%mod)*comb(n/mod,r/mod)%mod;
    }

private:
    vector<ll> fact,factinv;
    int mod;
    ll calc(int n, int r) {
        if(n<r||r<0||n<0) return 0;
        return fact[n]*factinv[r]%mod*factinv[n-r]%mod;
    }
};