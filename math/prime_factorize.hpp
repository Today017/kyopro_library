#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/primality_test.hpp"

/// @brief ポラードのロー法で n を素因数分解する
/// @note O(N^(1/4))
/// @ref https://qiita.com/t_fuki/items/7cd50de54d3c5d063b4a
/// @ref verify: https://algo-method.com/tasks/553
VP PrimeFactorize(ll n) {
    if(PrimalityTest(n)) return {{n,1}};
    auto find_factor=[](auto&& find_factor, ll n)-> ll {
        LL m=(ll)pow(n,0.125)+1;
        auto _gcd=[](LL a, LL b) {
            while(a) b%=a,swap(a,b);
            return b;
        };
        auto _abs=[](LL x) { return x<0?-x:x; };
        FOR(c,1,n) {
            auto f=[&](LL x) { return((x%n)*(x%n)+c)%n; };
            LL y=0,r=1,q=1,g=1,k=0,x=0,ys=0;
            while(g==1) {
                x=y;
                while(k<r*3/4) y=f(y),k++;
                while(k<r&&g==1) {
                    ys=y;
                    for(int i=0; i<min(m,r-k); i++) y=f(y),q=q*_abs(x-y)%n;
                    g=_gcd(q,n),k+=m;
                }
                k=r,r*=2;
            }
            if(g==n) {
                g=1,y=ys;
                while(g==1) y=f(y),g=_gcd(_abs(x-y),n);
            }
            if(g<n) {
                if(PrimalityTest(g)) return g;
                if(PrimalityTest(n/g)) return n/g;
                return find_factor(find_factor,g);
            }
        }
        return 0;
    };
    map<ll,ll> mp;
    ll i=2;
    while(i*i<=n) {
        ll k=0;
        while(n%i==0) n/=i,k++;
        if(k) mp[i]=k;
        i+=i%2+1;
        if(i==101&&n>=(1ll<<20)) {
            while(n>1) {
                if(PrimalityTest(n)) mp[n]=1,n=1;
                else {
                    ll j=find_factor(find_factor,n);
                    k=0;
                    while(n%j==0) n/=j,k++;
                    mp[j]=k;
                }
            }
        }
    }
    if(n>1) mp[n]=1;
    VP ret;
    for(auto p:mp) ret.push_back(p);
    sort(ALL(ret));
    return ret;
}