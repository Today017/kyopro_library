#include"../../kyopro_library/template.hpp"

/// オイラーの totient 関数
// totient(n) : n 以下で n と互いに素な自然数の個数を返す。
// O(sqrt(N))
ll totient(ll n){
	// totient(n) = n * (1-1/p1) * (1-1/p2) * ... * (1-1/pk) (p1,p2,...,pk は n の素因数)
	ll ret=n;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			ret-=ret/i;
			while(n%i==0)n/=i;
		}
	}
	if(n>1)ret-=ret/n;
	return ret;
}