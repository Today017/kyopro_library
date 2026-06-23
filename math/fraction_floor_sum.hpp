#pragma once
#include "../../kyopro_library/others/kth_root.hpp"

/// @brief Σ[i=1~N]floor(N/i) を求める
/// @note O(sqrt(N))
/// @note https://atcoder.jp/contests/abc230/tasks/abc230_e
ll FractionFloorSum(ll N) {
    ll r = KthRoot(N, 2);

    ll ret = 0;
    // 1 <= k <= sqrt(N) について、主客転倒
    // k <= N/i < k+1
    // N/(k+1) < i <= N/k
    // floor(N/i) = k なる i は N/k - N/(k+1) 個存在する
    for(ll i = 1; i <= r; i++) ret += ((N / i) - (N / (i + 1))) * i;

    // floor(N/i) >= sqrt(N)+1 なる i は高々 sqrt(N) 個
    for(ll i = 1; i <= N / (r + 1); i++) ret += N / i;

    return ret;
}
