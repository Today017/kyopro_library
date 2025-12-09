#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/fps.hpp"

/// @brief n 次多項式 f について、n 個の点 x[i] における f(x[i]) を返す
/// @note O(n (log(n))^2)
Poly MultipointEvaluate(Poly f, Poly x) {
    int n=x.size();
    if(n==0) return{};
    if(n==1) {
        Mod998 ret=0, tmp=1;
        for(Mod998 a: f) ret+=a*tmp, tmp*=x[0];
        return {ret};
    }
    int n2=1;
    while(n2<n) n2<<=1;
    vector<Poly> g(n2*2,{1});
    for(int i=0; i<n; i++) g[n2+i]={-x[i],1};
    for(ll i=n2-1; i>0; i--) g[i]=FPS::Mul(g[i<<1],g[i<<1|1]);

    g[1]=FPS::Div(f,g[1]).second;
    for(int i=2; i<n2+n; i++) g[i]=FPS::Div(g[i>>1],g[i]).second;
    Poly ret(n);
    for(int i=0; i<n; i++) ret[i]=g[n2+i][0];
    return ret;
}