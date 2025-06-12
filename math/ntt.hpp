#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"

/// @brief NTT Friendly 素数用 NTT 構造体
template<ll MOD, ll primitive_root>
class NTT {
    int divector<int>de_max,n;
    vector<ll> roots,inv_roots,tmp;

    void ntt(vector<ll>& a, bool inv=false) {
        int mask=n-1,p=0;
        for(int i=n>>1; i>=1; i>>=1) {
            auto& cur=(p&1)?tmp:a;
            auto& nxt=(p&1)?a:tmp;
            ll e=inv?roots[p+1]:inv_roots[p+1];
            ll w=1;
            for(int j=0; j<n; j+=i) {
                REP(k,i) nxt[j+k]=(cur[((j<<1)&mask)+k]+w*cur[(((j<<1)+i)&mask)+k])%MOD;
                (w*=e)%=MOD;
            }
            p++;
        }
        if(p&1) swap(a,tmp);
        if(inv) {
            int inv_sz=ModInv(n,MOD);
            for(int i=0; i<n; i++) (a[i]*=inv_sz)%=MOD;
        }
    }

public:
    NTT() {
        divector<int>de_max=1;
        ll n=MOD-1;
        while(n%2==0) n>>=1,divector<int>de_max++;
        roots=vector<ll>(divector<int>de_max+1);
        inv_roots=vector<ll>(divector<int>de_max+1);
        roots[0]=inv_roots[0]=1;
        for(int i=1; i<=divector<int>de_max; i++) {
            roots[i]=ModPow(primitive_root,(MOD-1)/(1<<i),MOD);
            inv_roots[i]=ModInv(roots[i],MOD);
        }
    }

    /// @brief a, b の畳み込み mod M を求める
    vector<ll> convolve(vector<ll> a, vector<ll> b) {
        n=1;
        while(n+1<a.size()+b.size()) n<<=1;
        tmp=vector<ll>(n); 

        vector<ll> fa(n), fb(n);
        for(int i=0; i<a.size(); i++) fa[i]=a[i];
        for(int i=0; i<b.size(); i++) fb[i]=b[i];

        ntt(fa); ntt(fb);
        for(int i=0; i<n; i++) (fa[i]*=fb[i])%=MOD;
        ntt(fa,true);

        while(fa.size()+1>a.size()+b.size()) fa.pop_back();
        return fa;
    }
};