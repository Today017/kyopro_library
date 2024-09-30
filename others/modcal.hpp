#include "../../kyopro_library/template.hpp"

ll modPow(ll x, ll n, ll mod) {
    ll ret = 1;
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
