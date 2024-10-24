#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/modcal.hpp"
#include "../../kyopro_library/math/rho.hpp"

// n の原始根を求める
// verify: https://judge.yosupo.jp/problem/primitive_root
ll primitiveRoot(ll n) {
    if (!primalityTest(n)) return -1;
    if (n == 2) return 1;
    auto pf = primeFactorize(n - 1);
    for (ll i = 2; i < n; i++) {
        bool ok = true;
        for (auto [p, _] : pf) {
            if (modPow(i, (n - 1) / p, n) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return i;
    }
    return -1;
}