#include"../../kyopro_library/template.hpp"

template<typename T>
struct Combination{
	vector<T>fact,factinv;
	Combination(int n){
		fact=vector<T>(n+1);
		factinv=vector<T>(n+1);
		fact[0]=1;
		for(int i=1;i<=n;i++)fact[i]=fact[i-1]*i;
		factinv[n]=fact[n].inv();
		for(int i=n;i>=1;i--)factinv[i-1]=factinv[i]*i;
	}
	T nCr(ll n,ll r){
		if(n<0||r<0||n-r<0)return 0;
	   return fact[n]*factinv[r]*factinv[n-r];
	}
	T nPr(ll n,ll r){
		if(n<0||r<0||n-r<0)return 0;
		return fact[n]*factinv[n-r];
	}
	T operator()(ll n,ll r){return nCr(n,r);}
};