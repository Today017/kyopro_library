#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/modcal.hpp"

/// @brief Ai=B (mod M) なる最小のiを求める
/// @brief 存在しないときは-1
ll Throne(ll A, ll B, ll M) {
    ll g = gcd(A, M);
    if(B % g) return -1;
    A /= g;
    B /= g;
    M /= g;
    ll ret = ModInv(A, M);
    (ret *= B) %= M;
    return ret;
}
