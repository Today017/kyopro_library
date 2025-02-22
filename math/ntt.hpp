#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"

// 数論変換
// O(N log(N))
// f(x) = Σ a[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数 mod 998244353 を返す。
vector<Mod998> NTT998(vector<Mod998> a,bool inv=false){
	int n=a.size(),h=0;
	while((1<<h)<n)h++;
	for(int i=0;i<n;i++){
		int j=0;
		// ビットを逆に
		for(int k=0;k<h;k++)j|=(i>>k&1)<<(h-1-k);
		if(i<j)swap(a[i],a[j]);
	}

	const vector<Mod998> rt={1,998244352,911660635,372528824,929031873,452798380,922799308,781712469,476477967,166035806,258648936,584193783,63912897,350007156,666702199,968855178,629671588,24514907,996173970,363395222,565042129,733596141,267099868,15311432};
    const vector<Mod998> irt={1,998244352,86583718,509520358,337190230,87557064,609441965,135236158,304459705,685443576,381598368,335559352,129292727,358024708,814576206,708402881,283043518,3707709,121392023,704923114,950391366,428961804,382752275,469870224};

	for(int b=1,t=1;b<n;b<<=1,t++){
		Mod998 w=1,base=inv?irt[t]:rt[t];
		for(int j=0;j<b;j++){
			// w := 1 の b 乗根の j 乗
			for(int k=0;k<n;k+=b*2){
				Mod998 s=a[j+k],t=a[j+k+b]*w;
				a[j+k]=s+t,a[j+k+b]=s-t;
			}
			w*=base;
		}
	}

	if(inv){
		Mod998 inv_n=Mod998(n).inv();
		for(int i=0;i<n;i++)a[i]*=inv_n;
	}

	return a;
}

// 畳み込み
// C[i] = Σ A[j]B[i-j] mod 998244353
// O(N log(N))
// |a|+|b| <= 2^23 が必要
vector<Mod998> convolve998(vector<Mod998> a,vector<Mod998> b){
	int n=1;
	while(n<(int)a.size()+(int)b.size()-1)n<<=1;
	vector<Mod998> fa(n),fb(n);
	for(int i=0;i<(int)a.size();i++)fa[i]=a[i];
	for(int i=0;i<(int)b.size();i++)fb[i]=b[i];
	fa=NTT998(fa),fb=NTT998(fb);
	for(int i=0;i<n;i++)fa[i]*=fb[i];
	fa=NTT998(fa,true);
	while((int)fa.size()>(int)a.size()+(int)b.size()-1)fa.pop_back();
	return fa;
}