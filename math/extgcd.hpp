#include"../../kyopro_library/template.hpp"

// extGCD(a,b) -> {g,x,y} : g=gcd(a,b), ax+by=g
tuple<ll,ll,ll>extGCD(ll a,ll b){
	if(b==0)return {a,1,0};
	ll q=a/b,r=a%b;
	auto[g,s,t]=extGCD(b,r);
	ll x=t;
	ll y=s-q*t;
	return {g,x,y};
}

// a の mod 逆元を求める
// ax=1(mod m) <-> ax+my=1(mod m)
// gcd(a,m)=1 出ない場合、-1 を返す。
ll modInvGcd(ll a,ll mod){
	auto[g,x,y]=extGCD(a,mod);
	if(g!=1)return-1;
	return x%mod;
}