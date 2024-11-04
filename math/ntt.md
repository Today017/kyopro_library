[top](../README.md)

# [Number Theoretic Transform](./ntt.hpp)

`NTT<P>`
- $bmod{\,p}$ での畳み込み用構造体。

`vector<mint> ntt(vector<mint> a, bool inv = false)`
- $a$ に対して NTT を行う。
- `inv = true` で逆変換。
- $O(n \log n)$

`vector<mint> convolve(vector<mint> a, vector<mint> b)`
- $C = \sum_{k=0}^{n-1} A_k \cdot B_{n-1-k}$ なる $C$ を計算する。
- $O(n \log n)$ $(n = |A| + |B|)$