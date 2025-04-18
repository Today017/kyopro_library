#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"

/// @brief 数論変換
/// @note O(N log(N))
/// @details f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数 mod 998244353 に変換する
void NTT998(VM& a, bool inv=false){
    int n=a.size(),h=0;
    while((1<<h)<n) h++;
    REP(i,n){
        int j=0;
        // ビットを逆に
        REP(k,h) j|=(i>>k&1)<<(h-1-k);
        if(i<j) swap(a[i],a[j]);
    }

    const VM rt={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141,267099868,15311432};
    const VM irt={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804,382752275,469870224};

    for(int b=1,t=1; b<n; b<<=1,t++){
        Mod998 w=1,base=inv?irt[t]:rt[t];
        REP(j,b){
            // w := 1 の b 乗根の j 乗
            for(int k=0; k<n; k+=b*2){
                Mod998 s=a[j+k],t=a[j+k+b]*w;
                a[j+k]=s+t,a[j+k+b]=s-t;
            }
            w*=base;
        }
    }

    if(inv){
        Mod998 inv_n=Mod998(n).inv();
        REP(i,n) a[i]*=inv_n;
    }
}

/// @brief AとBの畳み込み C[i] = Σ A[j]B[i-j] mod 998244353 を返す
/// @note O(N log(N))
/// @attention |a|+|b| <= 2^23 が必要
VM Convolve998(VM a,VM b){
    int n=1;
    while(n+1<a.size()+b.size()) n<<=1;

    VM fa(n),fb(n);
    REP(i,a.size()) fa[i]=a[i]; REP(i,b.size()) fb[i]=b[i];
    NTT998(fa); NTT998(fb);
    REP(i,n) fa[i]*=fb[i];
    NTT998(fa,true);
    
    while(fa.size()+1>a.size()+b.size()) fa.pop_back();
    return fa;
}