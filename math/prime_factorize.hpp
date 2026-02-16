#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/primality_test.hpp"

///@brief ポラードのロー法で N を素因数分解する
///@note O(N^(1/4))
///@ref https://qiita.com/t_fuki/items/7cd50de54d3c5d063b4a
///@ref verify: https://algo-method.com/tasks/553
vector<pair<ll,ll>> PrimeFactorize(ll N) {
    using lll=__int128_t;
    if(PrimalityTest(N)) return {{N,1}};
    auto find_factor=[](auto&& find_factor, ll N)-> ll {
        lll m=(ll)pow(N,0.125)+1;
        auto _gcd=[](lll a, lll b) {
            while(a) b%=a,swap(a,b);
            return b;
        };
        auto _abs=[](lll x) { return x<0?-x:x; };
        for(ll c=1; c<=N; c++) {
            auto f=[&](lll x) { return((x%N)*(x%N)+c)%N; };
            lll y=0,r=1,q=1,g=1,k=0,x=0,ys=0;
            while(g==1) {
                x=y;
                while(k<r*3/4) y=f(y),k++;
                while(k<r&&g==1) {
                    ys=y;
                    rep(i,min(m,r-k)) y=f(y), q=q*_abs(x-y)%N;
                    g=_gcd(q,N); k+=m;
                }
                k=r; r*=2;
            }
            if(g==N) {
                g=1,y=ys;
                while(g==1) y=f(y), g=_gcd(_abs(x-y),N);
            }
            if(g<N) {
                if(PrimalityTest(g)) return g;
                if(PrimalityTest(N/g)) return N/g;
                return find_factor(find_factor,g);
            }
        }
        return 0;
    };
    map<ll,ll> mp;
    ll i=2;
    while(i*i<=N) {
        ll k=0;
        while(N%i==0) N/=i, k++;
        if(k) mp[i]=k;
        i+=i%2+1;
        if(i==101 && N>=(1ll<<20)) {
            while(N>1) {
                if(PrimalityTest(N)) mp[N]=1, N=1;
                else {
                    ll j=find_factor(find_factor,N);
                    k=0;
                    while(N%j==0) N/=j,k++;
                    mp[j]=k;
                }
            }
        }
    }
    if(N>1) mp[N]=1;
    vector<pair<ll,ll>> ret;
    for(auto p: mp) ret.push_back(p);
    sort(all(ret));
    return ret;
}