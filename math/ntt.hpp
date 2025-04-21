#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"

/// @brief NTT Friendly 素数用 NTT 構造体
template<ll MOD, ll primitive_root>
class NTT{
    int divide_max,n;
    VL roots,inv_roots,tmp;

    void ntt(VL& a, bool inv=false){
        int mask=n-1,p=0;
        for(int i=n>>1; i>=1; i>>=1){
            auto& cur=(p&1)?tmp:a;
            auto& nxt=(p&1)?a:tmp;
            ll e=inv?roots[p+1]:inv_roots[p+1];
            ll w=1;
            for(int j=0; j<n; j+=i){
                REP(k,i) nxt[j+k]=(cur[((j<<1)&mask)+k]+w*cur[(((j<<1)+i)&mask)+k])%MOD;
                (w*=e)%=MOD;
            }
            p++;
        }
        if(p&1) swap(a,tmp);
        if(inv){
            int inv_sz=ModInv(n,MOD);
            REP(i,n) (a[i]*=inv_sz)%=MOD;
        }
    }

public:
    NTT(){
        divide_max=1;
        ll n=MOD-1;
        while(n%2==0) n>>=1,divide_max++;
        roots=VL(divide_max+1);
        inv_roots=VL(divide_max+1);
        roots[0]=inv_roots[0]=1;
        FOR(i,1,divide_max+1){
            roots[i]=ModPow(primitive_root,(MOD-1)/(1<<i),MOD);
            inv_roots[i]=ModInv(roots[i],MOD);
        }
    }

    /// @brief a, b の畳み込み mod M を求める
    VL convolve(VL a, VL b){
        n=1;
        while(n+1<a.size()+b.size()) n<<=1;
        tmp=VL(n); 

        VL fa(n), fb(n);
        REP(i,a.size()) fa[i]=a[i]; REP(i,b.size()) fb[i]=b[i];
        ntt(fa); ntt(fb);
        REP(i,n) (fa[i]*=fb[i])%=MOD;
        ntt(fa,true);

        while(fa.size()+1>a.size()+b.size()) fa.pop_back();
        return fa;
    }
};