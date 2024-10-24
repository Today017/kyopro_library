#pragma once
#include "../../kyopro_library/template.hpp"

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

ll modInv(ll x, ll mod) {
    return modPow(x, mod - 2, mod);
}
