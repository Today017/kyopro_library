#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"

// 二項係数
// 階乗
template<typename mint=Mod998>
mint factrial(int n){
	static vector<mint>fac;
	if((int)fac.size()<=n){
		if(fac.empty())fac.push_back(1);
		for(int i=fac.size();i<=n;i++)fac.push_back(fac.back()*i);
	}
	return fac[n];
}

// 階乗逆元
template<typename mint=Mod998>
mint factinv(int n){
	static vector<mint>minv,finv;//逆元, 階乗逆元
	if((int)finv.size()<=n){
		//https://drken1215.hatenablog.com/entry/2018/06/08/210000
		if(minv.empty())minv.push_back(0),minv.push_back(1);
		for(int i=minv.size();i<=n;i++)minv.push_back(-minv[mint::get_mod()%i]*(mint::get_mod()/i));
		if(finv.empty())finv.push_back(1);
		for(int i=finv.size();i<=n;i++)finv.push_back(finv.back()*minv[i]);
	}
	return finv[n];
}

template<typename mint=Mod998>
mint comb(int n,int r){
	if(n<0||r<0||n-r<0)return 0;
	return factrial<mint>(n)*factinv<mint>(r)*factinv<mint>(n-r);
}

template<typename mint=Mod998>
mint perm(int n,int r){
	if(n<0||r<0||n-r<0)return 0;
	return factrial<mint>(n)*factinv<mint>(n-r);
}