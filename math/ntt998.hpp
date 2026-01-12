#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"

///@brief 数論変換
///@note O(N log(N))
///@details f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数 mod 998244353 に変換する
void NTT998(vector<Mod998>& a, bool inv=false) {
    static vector<Mod998> r, ir, tmp;
    if(r.empty()) {
        int dm=1; ll n=Mod998::mod()-1;
        while(n%2==0) n>>=1, dm++;
        r.resize(dm+1); ir.resize(dm+1); r[0]=ir[0]=1;
        for(int i=1; i<=dm; i++) {
            r[i]=Mod998(3).pow((Mod998::mod()-1)>>i);
            ir[i]=r[i].inv();
        }
    }
    tmp.resize(a.size());
    int n=a.size(), p=0;
    for(int i=n>>1; i; i>>=1, p++) {
        auto &cur=p&1? tmp: a, &nxt=p&1? a: tmp;
        Mod998 w=1, e=inv? r[p+1]: ir[p+1];
        for(int j=0; j<n; j+=i, w*=e) rep(k,i) {
            nxt[j+k]=cur[((j<<1)&(n-1))+k]+w*cur[(((j<<1)+i)&(n-1))+k];
        }
    }
    if(p&1) swap(a,tmp);
    if(inv) {
        Mod998 in=Mod998(n).inv();
        for(Mod998& x: a) x*=in;
    }
}

///@brief AとBの畳み込み C[i] = Σ A[j]B[i-j] mod 998244353 を返す
///@note O(N log(N))
///@attention |a|+|b| <= 2^23 が必要
///@ref verify: https://judge.yosupo.jp/problem/convolution_mod
vector<Mod998> Convolve998(vector<Mod998> a,vector<Mod998> b) {
    int n=1, z=a.size()+b.size();
    while(n+1<z) n<<=1;
    a.resize(n); b.resize(n);
    NTT998(a); NTT998(b);
    rep(i,n) a[i]*=b[i];
    NTT998(a,true);
    while(a.size()+1>z) a.pop_back();
    return a;
}