#include "../../kyopro_library/template.hpp"

namespace Ring {
    // 円環上で p1 -> p2 に + 方向に移動する際に target を通過するかを判定する。
    // verify: https://atcoder.jp/contests/abc367/tasks/abc367_a
    bool betweenIncrement(ll p1, ll p2, ll target) {
        if (p1 == p2) return p1 == target;
        return (target - p2) * (p2 - p1) * (p1 - target) >= 0;
    }

    // 円環上で p1 -> p2 に - 方向に移動する際に target を通過するかを判定する。
    bool betweenDecrement(ll p1, ll p2, ll target) {
        swap(p1, p2);
        return betweenIncrement(p1, p2, target);
    }

    // サイズ n の円環上で p1 -> p2 に移動する距離を返す。
    ll distanceMin(ll p1, ll p2, ll n) {
        if (p1 > p2) swap(p1, p2);
        return min(p2 - p1, n - (p2 - p1));
    }

    // サイズ n の円環上で p1 -> p2 に + 方向に移動する距離を返す。
    ll distanceIncrement(ll p1, ll p2, ll n) {
        return p1 < p2 ? p2 - p1 : (n + p2 - p1) % n;
    }

    // サイズ n の円環上で p1 -> p2 に - 方向に移動する距離を返す。
    ll distanceDecrement(ll p1, ll p2, ll n) {
        return p1 > p2 ? p1 - p2 : (n + p1 - p2) % n;
    }
}  // namespace Ring