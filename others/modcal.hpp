#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief x^n(mod m) を返す
/// @note O(log(m))
template<typename T=ll>
T ModPow(T x, T n, T mod){
	ll ret=1;
	if(typeid(T)==typeid(ll)&&mod>INF*2) return ModPow<__int128_t>(x,n,mod);
	while(n>0){
		if(n&1) (ret*=x)%=mod;
        (x*=x)%=mod;
		n>>=1;
	}
	return ret;
}