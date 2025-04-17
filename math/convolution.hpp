#include"../../kyopro_library/template.hpp"

/// @file convolution.hpp
/// @brief 高速フーリエ変換
/// @note O(N log(N))
/// @details f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数を返す。
/// @details a = (a[0], a[1], ..., a[n-1]) -> fa = (f(w^0), f(w^1), ..., f(w^(n-1)))
vector<complex<double>>FFT(vector<complex<double>>a,bool inv=false){
	int n=a.size(),h=0;
	while((1<<h)<n)h++;
	for(int i=0;i<n;i++){
		int j=0;
		//ビットを逆に
		for(int k=0;k<h;k++)j|=(i>>k&1)<<(h-1-k);
		if(i<j)swap(a[i],a[j]);
	}

	for(int b=1;b<n;b<<=1){
		for(int j=0;j<b;j++){
			//b = ブロックサイズの半分
			//j, j+b を計算
			//w = exp(-2πj / 2b) = 1 の b 乗根の j 乗
			complex<double>w=polar(1.0,(2.0*M_PI)/(2.0*b)*j*(inv?1:-1));
			//ブロックサイズ 2b だけずらしながら計算
			for(int k=0;k<n;k+=b*2){
				complex<double>s=a[j+k],t=a[j+k+b]*w;
				a[j+k]=s+t,a[j+k+b]=s-t;
			}
		}
	}

	if(inv)for(int i=0;i<n;i++)a[i]/=n;
	return a;
}

/// @brief 畳み込み
/// @note O(N log(N))
vector<double>Convolve(const vector<double>&a,const vector<double>&b){
	int n=1;
	while(n<(int)a.size()+(int)b.size()-1)n*=2;
	vector<complex<double>>fa(n),fb(n);
	for(int i=0;i<(int)a.size();i++)fa[i]=a[i];
	for(int i=0;i<(int)b.size();i++)fb[i]=b[i];
	// fa, fb を高速フーリエ変換
	fa=FFT(fa),fb=FFT(fb);
	// fa' * fb' を計算
	for(int i=0;i<n;i++)fa[i]*=fb[i];
	// fa' * fb' を逆高速フーリエ変換し、fa * fb の係数を得る
	fa=FFT(fa,true);
	vector<double>ret(n);
	for(int i=0;i<n;i++)ret[i]=fa[i].real();
	return ret;
}

/// @brief 整数での畳み込み
/// @note 整数の積が 10^12 を超える場合や N >= 2^20 の場合は特に誤差に注意。大きい値での畳み込みは NTT + Garner のアルゴリズムを使う。
vector<ll>Convolve(const vector<ll>&a,const vector<ll>&b){
	vector<double>da(a.size()),db(b.size());
	for(int i=0;i<(int)a.size();i++)da[i]=a[i];
	for(int i=0;i<(int)b.size();i++)db[i]=b[i];
	vector<double>ab=Convolve(da,db);
	vector<ll>ret(ab.size());
	for(int i=0;i<(int)ret.size();i++)ret[i]=(ll)floor(ab[i]+0.5);
	return ret;
}