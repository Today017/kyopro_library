[top](../README.md)

# Utils

### [`others/modcal.hpp`](./modcal.hpp)

`T=ll modPow(T a, T n, T p)`
- $a^n \mod p$ を返す。
- 基本的には `ll` だが、 $p^2$ が `ll` の範囲を超える場合は `__int128_t` になる。
- $O(\log n)$

`T modInv(T a, T p)`
- $a^{-1} \mod p$ を返す。
- $p$ は素数。
- $O(\log p)$

### [`others/kth_root.hpp`](./kth_root.hpp)

`u64 kthRoot(u64 n, ll k = 2)`
- $\lfloor \sqrt[k]{n} \rfloor$ を返す。
- $O(\log MAX(=10^{10}) \log k)$

### [`others/arith.hpp`](./arith.hpp)

`ArithmeticProgression`
- 等差数列を表す構造体。
- `start`: 初項
- `goal`: 末項
- `step`: 公差
- `length()`: 長さ

`ll arithmeticSum(ArithmeticProgression ap)`
- 等差数列の和を返す。

### [`others/intersect.hpp`](./intersect.hpp)

`bool haveIntersection(ll l1, ll r1, ll l2, ll r2)`
- 区間 $[l_1, r_1]$ と区間 $[l_2, r_2]$ が共通部分を持つか否かを返す。
- $O(1)$

### [`others/ring.hpp`](./ring.hpp)
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

### [`others/bit.hpp`](./bit.hpp)
`namespace Bit` に定義されている。

`int popcount(T x)`
- $x$ のビット表現に含まれる $1$ の数を返す。

`int parity(T x)`
- $x$ のビット表現に含まれる $1$ の数が偶数なら0、奇数なら $1$ を返す。

`int topBit(T x)`
- $x$ のビット表現で最上位の $1$ の位置を返す。
- $x=0$ のときは -1 を返す。

`int lowBit(T x)`
- $x$ のビット表現で最下位の $1$ の位置を返す。
- $x=0$ のときは -1 を返す。

`bool isPowerOfTwo(T x)`
- $x$ が $2$ の冪乗か否かを返す。

`ll mask(int n)`
- $n$ ビット目までが立っているビットマスクを返す。

`ll hasBit(ll x, int i)`
- $x$ の $i$ ビット目が立っているか否かを返す。

`string toBinary(ll x, int len = 32, bool rev = false)`
- $x$ のビット表現を文字列で返す。
- `len`: ビット数
- `rev`: 値の小さいビットから出力するか否か