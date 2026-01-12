#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/fps.hpp"

vector<Mod998> BerlekampMassey(const vector<Mod998>& s) {
    int n=s.size();
    vector<Mod998> c{1}, b{1};
    int l=0, m=1;
    Mod998 bb=1;
    rep(i,n) {
        Mod998 d=0;
        for(int j=0; j<=l; j++) d+=c[j]*s[i-j];
        if(d==Mod998(0)) m++;
        else if(2*l<=i) {
            auto t=c; Mod998 coef=d*bb.inv();
            if(c.size()<b.size()+m) c.resize(b.size()+m,0);
            rep(j,b.size()) c[j+m]-=coef*b[j];
            l=i+1-l; b=t; bb=d; m=1;
        } else {
            Mod998 coef=d*bb.inv();
            if(c.size()<b.size()+m) c.resize(b.size()+m,0);
            rep(j,b.size()) c[j+m]-=coef*b[j];
            m++;
        }
    }
    if(!c.empty()) c.erase(c.begin());
    for(auto& x: c) x=-x;
    return c;
}

Mod998 BostanMori(Poly num, Poly den, ll n) {
    while(n>0) {
        Poly den_neg=den;
        rep(i,den_neg.size()) if(i%2==1) den_neg[i]=-den_neg[i];

        Poly f2=FPS::Mul(num,den_neg), g2=FPS::Mul(den,den_neg);
        Poly num2, den2;
        for(int i=n%2; i<f2.size(); i+=2) num2.push_back(f2[i]);
        for(int i=0; i<g2.size(); i+=2) den2.push_back(g2[i]);

        num.swap(num2); den.swap(den2);
        n/=2;
    }

    return num[0]*den[0].inv();
}

Mod998 LinearRecurrence(vector<Mod998> a, vector<Mod998> c, ll k) {
    int n=c.size();
    if(n==0) return 0;
    vector<Mod998> dnm(n+1); dnm[0]=1;
    rep(i,n) dnm[i+1]=-c[i];
    a.resize(n,0);
    auto num=Convolve998(dnm,a); if(num.size()>n) num.resize(n);
    return FPS::BostanMori(k,num,dnm);
}

Mod998 BMBM(const vector<Mod998> &s, ll n) {
  auto bm=BerlekampMassey(s);
  return LinearRecurrence(s,bm,n);
}
