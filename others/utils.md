[top](../README.md)

# Utils

### `others/modcal.hpp`

[`T=ll modPow(T a, T n, T p)`](./modcal.hpp)
- $a^n \mod p$ を返す。
- 基本的には `ll` だが、 $p^2$ が `ll` の範囲を超える場合は `__int128_t` になる。
- $O(\log n)$

[`ll modInv(ll a, ll p)`](./modcal.hpp)
- $a^{-1} \mod p$ を返す。
- $p$ は素数。
- $O(\log p)$

### `others/kth_root.hpp`

[`u64 kthRoot(u64 n, ll k = 2)`](./kth_root.hpp)
- $\lfloor \sqrt[k]{n} \rfloor$ を返す。
- $O(\log MAX(=10^{10}) \log k)$

### `others/arith.hpp`

[`ArithmeticProgression`](./arith.hpp)
- 等差数列を表す構造体。
- `start`: 初項
- `goal`: 末項
- `step`: 公差
- `length()`: 長さ

`ll arithmeticSum(ArithmeticProgression ap)`
- 等差数列の和を返す。

### `others/intersect.hpp`

[`bool haveIntersection(ll l1, ll r1, ll l2, ll r2)`](./intersect.hpp)
- 区間 $[l_1, r_1]$ と区間 $[l_2, r_2]$ が共通部分を持つか否かを返す。
- $O(1)$

### `others/ring.hpp`
`namespace Ring` に定義されている。

`bool betweenIncrement(ll p1, ll p2, ll target)`
- 円環上で $p1$ から $p2$ に + 方向に進むとき、 $target$ を通過するか否かを返す。
- 円環上の閉区間 $[p1, p2]$ に $target$ が含まれるか否かを判定する。

`bool betweenDecrement(ll p1, ll p2, ll target)`
- 円環上で $p1$ から $p2$ に - 方向に進むとき、 $target$ を通過するか否かを返す。

`ll distanceRing(ll p1, ll p2, ll n)`
- サイズ $n$ の円環上での $p1$ から $p2$ までの距離を返す。

`ll distanceIncrement(ll p1, ll p2, ll n)`
- サイズ $n$ の円環上での $p1$ から $p2$ に + 方向に進むときの距離を返す。

`ll distanceDecrement(ll p1, ll p2, ll n)`
- サイズ $n$ の円環上での $p1$ から $p2$ に - 方向に進むときの距離を返す。