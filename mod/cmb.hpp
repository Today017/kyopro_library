#include"../../kyopro_library/template.hpp"

template<typename T>
struct Combinatorics{
	Combinatorics(int n){
		fac=vector<T>(n+1);
		finv=vector<T>(n+1);
		fac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
		finv[n]=fac[n].inv();
		for(int i=n;i>=1;i--)finv[i-1]=finv[i]*i;
	}
	T comb(ll n,ll r){
		if(n<0||r<0||n-r<0)return 0;
	   return fac[n]*finv[r]*finv[n-r];
	}
	T perm(ll n,ll r){
		if(n<0||r<0||n-r<0)return 0;
		return fac[n]*finv[n-r];
	}
	T fact(int n){return fac[n];}
	T factinv(int n){return finv[n];}
	T operator()(ll n,ll r){return comb(n,r);}

private:
	vector<T>fac,finv;
};
