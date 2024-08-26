[top](../README.md)

# [Combination (Lucas)](./lucas.hpp)


`CombinationLucas(int mod)`
- Lucas の定理を用いて $_n C_r \pmod{mod}$ を求めるための前計算を行う。
- $O(mod)$

`ll nCr(ll n, ll r)`
- Lucas の定理を用いて $_n C_r \pmod{mod}$ を求める。
- $O(\log_{p}{n})$


`Combination` ライブラリでは、 $n\ge p$ に対して $_n C_r \pmod{p}$  を求める際に正しい計算ができないため、Lucas の定理を用いて計算を行う必要がある。

### Lucas の定理
$p$ を素数とし、 $n, r$ を非負整数とする。

また、 $n = n_k p^k + n_{k-1} p^{k-1} + \cdots + n_1 p + n_0$、$r = r_k p^k + r_{k-1} p^{k-1} + \cdots + r_1 p + r_0$ と表す。

このとき、

$_n C_r \pmod{p}= \prod_{k=0}^{N}{_{n_k}C_{r_k}} \pmod{p}$
