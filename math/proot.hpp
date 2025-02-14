#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"
#include"../../kyopro_library/math/rho.hpp"
#include"../../kyopro_library/others/xor128.hpp"

//n の原始根を求める
//ref: https://37zigen.com/primitive-root/
//verify: https://judge.yosupo.jp/problem/primitive_root
ll primitiveRoot(ll n){
	if(!primalityTest(n))return-1;
	if(n==2)return 1;
	auto pf=primeFactorize(n-1);
	while(true){
		ll i=xor128(2,n);
		bool ok=true;
		for(auto[p,_]:pf){
			if(modPow(i,(n-1)/p,n)==1){
				ok=false;
				break;
			}
		}
		if(ok)return i;
	}
	return-1;
}