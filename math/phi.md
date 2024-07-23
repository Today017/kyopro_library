[top](../README.md)

# Euler's Totient Function

[`ll totient(ll n)`](./phi.hpp)
- 自然数 $n$ 以下であって $n$ と互いに素な数の個数を返す。
- $O(\sqrt{n})$

[`vector<int> totientTable(int n)`](./phip.hpp)
- $n$ 以下の自然数について、それぞれのオイラーの $\phi$ 関数の値を前計算する。
- $O(n\log{\log{n}})$