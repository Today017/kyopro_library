#include"../../kyopro_library/template.hpp"

/// @brief 高速フーリエ変換
/// @note O(N log(N))
/// @details f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数を返す。
/// @details a = (a[0], a[1], ..., a[n-1]) -> fa = (f(w^0), f(w^1), ..., f(w^(n-1)))
void FFT(vector<complex<double>>& a, bool inv=false){
    int n=a.size(),h=0;
    while((1<<h)<n) h++;
    REP(i,n){
        int j=0;
        //ビットを逆に
        REP(k,h) j|=(i>>k&1)<<(h-1-k);
        if(i<j) swap(a[i],a[j]);
    }

    for(int b=1; b<n; b<<=1){
        REP(j,b){
            //b = ブロックサイズの半分
            //j, j+b を計算
            //w = exp(-2πj / 2b) = 1 の b 乗根の j 乗
            complex<double> w=polar(1.0,(2.0*M_PI)/(2.0*b)*j*(inv?1:-1));
            //ブロックサイズ 2b だけずらしながら計算
            for(int k=0; k<n; k+=b*2){
                complex<double> s=a[j+k],t=a[j+k+b]*w;
                a[j+k]=s+t,a[j+k+b]=s-t;
            }
        }
    }

    if(inv)REP(i,n) a[i]/=n;
}

/// @brief 畳み込み
/// @note O(N log(N))
vector<double>Convolve(const vector<double>& a, const vector<double>& b){
    int n=1;
    while(n+1<a.size()+b.size()) n*=2;
    vector<complex<double>> fa(n),fb(n);
    REP(i,a.size()) fa[i]=a[i]; REP(i,b.size()) fb[i]=b[i];

    // fa, fb を高速フーリエ変換
    FFT(fa); FFT(fb);
    // fa' * fb' を計算
    REP(i,n) fa[i]*=fb[i];
    // fa' * fb' を逆高速フーリエ変換し、fa * fb の係数を得る
    FFT(fa,true);

    vector<double> ret(n); REP(i,n) ret[i]=fa[i].real();
    return ret;
}

/// @brief 整数での畳み込み
/// @note 整数の積が 10^12 を超える場合や N >= 2^20 の場合は特に誤差に注意。大きい値での畳み込みは NTT + Garner のアルゴリズムを使う。
VL Convolve(const VL& a, const VL& b){
    vector<double> da(a.size()),db(b.size());
    REP(i,a.size()) da[i]=a[i]; REP(i,b.size()) db[i]=b[i];
    vector<double> ab=Convolve(da,db);

    VL ret(ab.size());
    REP(i,ret.size()) ret[i]=(ll)floor(ab[i]+0.5);
    return ret;
}