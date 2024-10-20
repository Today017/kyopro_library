#include "../../kyopro_library/template.hpp"

// 円環上で p1 -> p2 に移動する際に target を通過するかを判定する。
// verify: https://atcoder.jp/contests/abc367/tasks/abc367_a
bool betweenOnRing(ll p1, ll p2, ll target) {
    return (target - p2) * (p2 - p1) * (p1 - target) > 0;
}