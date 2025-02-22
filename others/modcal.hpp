#pragma once
#include "../../kyopro_library/template.hpp"

// modPow(x, n, m) : x^n (mod m) を返す
// O(log(m))
template <typename T = ll>
T modPow(T x, T n, T mod) {
	ll ret = 1;
	if (typeid(T) == typeid(ll) && mod > INF * 2) return modPow<__int128_t>(x, n, mod);
	while (n > 0) {
		if (n & 1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

// modInv(x, m) : x*y = 1 (mod m) なる y を返す
// O(log(m))
// ただし、m は素数
ll modInv(ll x, ll mod) {return modPow(x, mod - 2, mod);}