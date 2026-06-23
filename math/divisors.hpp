#pragma once
#include "../../kyopro_library/math/prime_factorize.hpp"

/// @brief 約数列挙
vector<i64> Divisors(i64 N) {
    if(N == 0) return {};
    auto v = PrimeFactorize(N);

    vector<i64> ret;
    auto f = [&](auto&& f, ii i, i64 x) -> void {
        if(i == siz(v)) {
            ret.push_back(x);
            return;
        }
        f(f, i + 1, x);
        rep(j, v[i].second) f(f, i + 1, x *= v[i].first);
    };
    f(f, 0, 1);
    sort(all(ret));
    return ret;
}
