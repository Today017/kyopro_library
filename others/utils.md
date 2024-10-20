[top](../README.md)

# Utils

### `others/modcal.hpp`

[`ll modPow(ll a, ll n, ll p)`](./modcal.hpp)
- $a^n \mod p$ を返す。
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
- 区間 $[l_1, r_1]$ と区間 $[l_2, r_2]$ が共通部分を持つかどうかを返す。
- $O(1)$

### `others/bet_ring.hpp`

[`bool betweenOnRing(ll p1, ll p2, ll target)`](./bet_ring.hpp)
- 点 $p_1$ と点 $p_2$ を通る円周上に点 $target$ があるかどうかを返す。
