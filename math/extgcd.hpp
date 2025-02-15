#include"../../kyopro_library/template.hpp"

// extGCD(a,b) -> {g,x,y} : g = gcd(a,b), ax+by = g
/*
	gcd(a,b) = gcd(b%a,a), gcd(b,0) = b と b%a + (b/a)*a = b を使う。
	ax + by = g なる x,y を求めたい。
	今、(b%a)X + aY = g なる X, Y が分かっている。
	(b%a)X = bX - (b/a)*a*X より、これを代入して、
	bX - (b/a)*a*X + aY = g
	a(Y-(b/a)*X) + bX = g
*/
tuple<ll,ll,ll>extGCD(ll a,ll b){
	if(a==0)return {b,0,1};
	auto[g,s,t]=extGCD(b%a,a);
	return{g,t-(b/a)*s,s};
}

// a^(-1) (mod m)
// gcd(a,m)=1 でない場合、-1 を返す。
ll modInvGcd(ll a,ll m){
	// ax = 1 (mod m) <-> ax+my = 1 (mod m)
	auto[g,x,y]=extGCD(a,m);
	if(g!=1)return-1;
	return (x+m)%m;
}
