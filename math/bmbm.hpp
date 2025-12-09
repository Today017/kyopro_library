#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/fps.hpp"

vector<Mod998> BerlekampMassey(const vector<Mod998>& s) {
    int n=s.size();
    vector<Mod998> c{1}, b{1};
    int l=0, m=1;
    Mod998 bb=1;
    for(int i=0; i<n; i++) {
        Mod998 d=0;
        for(int j=0; j<=l; j++) d+=c[j]*s[i-j];
        if(d==Mod998(0)) m++;
        else if(2*l<=i) {
            auto t=c; Mod998 coef=d*bb.inv();
            if(c.size()<b.size()+m) c.resize(b.size()+m,0);
            for(int j=0; j<b.size(); j++) c[j+m]-=coef*b[j];
            l=i+1-l; b=t; bb=d; m=1;
        } else {
            Mod998 coef=d*bb.inv();
            if(c.size()<b.size()+m) c.resize(b.size()+m,0);
            for(int j=0; j<b.size(); j++) c[j+m]-=coef*b[j];
            m++;
        }
    }
    if(!c.empty()) c.erase(c.begin());
    for(auto& x: c) x=-x;
    return c;

    // const int N = (int)f.size(); vector<Mod998> b, c;
    // b.reserve(N + 1); c.reserve(N + 1); b.push_back(Mod998(1)); c.push_back(Mod998(1));
    // Mod998 y = Mod998(1);
    // for (int ed = 1; ed <= N; ed++) {
    //     int l = int(c.size()), m = int(b.size()); Mod998 x = 0;
    //     for (int i = 0; i < l; i++) x += c[i] * f[ed - l + i];
    //     b.emplace_back(Mod998(0)); m++;
    //     if (x == Mod998(0)) continue;
    //     Mod998 freq = x / y;
    //     if (l < m) {
    //         auto tmp = c; c.insert(begin(c), m - l, Mod998(0));
    //         for (int i = 0; i < m; i++) c[m - 1 - i] -= freq * b[m - 1 - i];
    //         b = tmp; y = x;
    //     } else {
    //         for (int i = 0; i < m; i++) c[l - 1 - i] -= freq * b[m - 1 - i];
    //     }
    // }
    // reverse(begin(c), end(c));

    // return c;
}

Mod998 bostanMori(std::vector<Mod998> num, std::vector<Mod998> den, long long n) {
  while (n > 0) {
    // den_neg = den with odd coefficients negated
    std::vector<Mod998> den_neg = den;
    for (size_t i = 0; i < den_neg.size(); ++i) {
      if (i % 2 == 1) den_neg[i] = Mod998(0) - den_neg[i];
    }

    // f2 = num * den_neg
    // g2 = den * den_neg
    std::vector<Mod998> f2 = Convolve998(num, den_neg);
    std::vector<Mod998> g2 = Convolve998(den, den_neg);

    std::vector<Mod998> num2, den2;
    // pick even or odd coefficients depending on parity of n
    if (n % 2 == 0) {
      for (size_t i = 0; i < f2.size(); i += 2) num2.push_back(f2[i]);
    } else {
      for (size_t i = 1; i < f2.size(); i += 2) num2.push_back(f2[i]);
    }
    for (size_t i = 0; i < g2.size(); i += 2) den2.push_back(g2[i]);

    num = std::move(num2);
    den = std::move(den2);
    n /= 2;
  }
  return num[0] * den[0].inv();
}

Mod998 LinearRecurrence(vector<Mod998> a, vector<Mod998> c, ll k) {
    int n=c.size();
    if(n==0) return 0;
    vector<Mod998> dnm(n+1); dnm[0]=1;
    rep(i,n) dnm[i+1]=-c[i];
    a.resize(n,0);
    auto num=Convolve998(dnm,a); if(num.size()>n) num.resize(n);
    return FPS::BostanMori(k,num,dnm);
    // return bostanMori(num,dnm,k);
}

Mod998 BMBM(const vector<Mod998> &s, ll n) {
  auto bm=BerlekampMassey(s);
  return LinearRecurrence(s,bm,n);
}