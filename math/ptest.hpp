#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/modcal.hpp"

// ミラーラビン素数判定法
// O(k log^3 n)
// verify: https://judge.yosupo.jp/problem/primality_test
bool primalityTest(ll n) {
    if (n == 2) return true;
    if (n <= 1 || n % 2 == 0) return false;
    vector<ll> test;
    if (n < 4759123141ll) {
        test = {2, 7, 61};
    } else {
        test = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    }
    ll s = 0, d = n - 1;
    while (d % 2 == 0) {
        d >>= 1;
        s++;
    }
    for (ll a : test) {
        if (a >= n) break;
        __int128_t x = modPow<__int128_t>(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        } else {
            for (ll r = 1; r < s; r++) {
                x = x * x % n;
                if (x == 1) {
                    return false;
                } else if (x == n - 1) {
                    break;
                }
            }
        }
        if (x != n - 1) return false;
    }
    return true;
}
