#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"

/// @brief 数論変換
/// @note O(N log(N))
/// @details f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数 mod 998244353 に変換する
void NTT998(vector<Mod998>& a, bool inv=false) {
    static bool flag=false;
    static int divide_max;
    static vector<Mod998> roots, inv_roots, tmp;
    if(!flag) {
        flag=true;
        divide_max=1;
        ll n=998244353-1;
        while(n%2==0) n>>=1,divide_max++;
        roots=vector<Mod998>(divide_max+1);
        inv_roots=vector<Mod998>(divide_max+1);
        roots[0]=inv_roots[0]=1;
        for(int i=1; i<=divide_max; i++) {
            roots[i]=Mod998(3).pow((998244353-1)/(1<<i));
            inv_roots[i]=roots[i].inv();
        }
    }

    tmp=vector<Mod998>(a.size());
    int n=a.size(), mask=n-1, p=0;
    for(int i=n>>1; i>=1; i>>=1) {
        auto& cur=((p&1) ? tmp : a);
        auto& nxt=((p&1) ? a : tmp);
        Mod998 e=(inv ? roots[p+1] : inv_roots[p+1]);
        Mod998 w=1;
        for(int j=0; j<n; j+=i) {
            rep(k,i) nxt[j+k]=cur[((j<<1)&mask)+k]+w*cur[(((j<<1)+i)&mask)+k];
            w*=e;
        }
        p++;
    }
    if(p&1) swap(a,tmp);
    if(inv) {
        Mod998 inv_sz=Mod998(n).inv();
        for(int i=0; i<n; i++) a[i]*=inv_sz;
    }
}

/// @brief AとBの畳み込み C[i] = Σ A[j]B[i-j] mod 998244353 を返す
/// @note O(N log(N))
/// @attention |a|+|b| <= 2^23 が必要
vector<Mod998> Convolve998(vector<Mod998> a,vector<Mod998> b) {
    int n=1;
    while(n+1<a.size()+b.size()) n<<=1;

    vector<Mod998> fa(n), fb(n);
    for(int i=0; i<a.size(); i++) fa[i]=a[i];
    for(int i=0; i<b.size(); i++) fb[i]=b[i];

    NTT998(fa); NTT998(fb);
    for(int i=0; i<n; i++) fa[i]*=fb[i];
    NTT998(fa,true);
    
    while(fa.size()+1>a.size()+b.size()) fa.pop_back();
    return fa;
}