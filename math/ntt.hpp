#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"

/// @brief NTT Friendly 素数用 NTT 構造体
template<ll MOD, ll primitive_root>
class NTT{
    int divide_max;
    VL roots,inv_roots;

    void ntt(VL& a, bool inv=false){
        int n=a.size();
        int h=0;
        while((1<<h)<n) h++;
        REP(i,n){
            int j=0;
            REP(k,h) j|=(i>>k&1)<<(h-1-k);
            if(i<j) swap(a[i],a[j]);
        }
        for(int b=1,t=1; b<n; b<<=1,t++){
            ll w=1,base=inv?inv_roots[t]:roots[t];
            REP(j,b){
                for(int k=0; k<n; k+=b*2){
                    ll s=a[j+k];
                    ll t=(a[j+k+b]*w)%MOD;
                    (a[j+k]=s+t)%=MOD;
                    (a[j+k+b]=s-t+MOD)%=MOD;
                }
                (w*=base)%=MOD;
            }
        }
        if(inv){
            ll inv_n=ModInv(n,MOD);
            REP(i,n) (a[i]*=inv_n)%=MOD;
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

    /// @brief a, b の畳み込みを求める
    VL convolve(VL a, VL b){
        int n=1;
        while(n+1<a.size()+b.size()) n<<=1;

        VL fa(n),fb(n);
        REP(i,a.size()) fa[i]=a[i]; REP(i,b.size()) fb[i]=b[i];
        ntt(fa); ntt(fb);
        REP(i,n) (fa[i]*=fb[i])%=MOD;
        ntt(fa,true);

        while(fa.size()+1>a.size()+b.size()) fa.pop_back();
        return fa;
    }
};