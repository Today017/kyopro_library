#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief LIS
/// @brief 配列 V の最長増加部分列の長さを返す
/// @param strict `true` のとき狭義単調増加
/// @note O(N log(N))
int LisLength(vi& V, bool strict = true) {
    int N = V.size();
    vi dp(N, INFL);
    rep(i, N) {
        int idx = (strict ? lower_bound(all(dp), V[i]) : upper_bound(all(dp), V[i])) - dp.begin();
        dp[idx] = V[i];
    }
    rep(i, N) if(dp[i] == INFL) return i;
    return N;
}