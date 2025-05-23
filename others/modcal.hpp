#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief x^n (mod m) を返す
template<typename T=ll>
T ModPow(T x, T n, T mod) {
    T ret=1;
    if(typeid(T)==typeid(ll)&&mod>INF*2) return ModPow<lll>(x,n,mod);
    while(n>0) {
        if(n&1) (ret*=x)%=mod;
        (x*=x)%=mod;
        n>>=1;
    }
    return ret;
}

/// @brief x^(-1) (mod m) を返す
ll ModInv(ll a, ll m) {
    ll b=m,u=1,v=0;
    while(b) {
        ll t=a/b;
        a-=t*b; swap(a,b);
        u-=t*v; swap(u,v);
    }
    return (u+m)%m;
}