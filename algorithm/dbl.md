[top](../README.md)

# [Doubling](./dbl.hpp)

`Doubling<int Log>(vector<int> a)`
- 各状態の 1 つ先の状態を記録した配列 $a$ からダブリングテーブルを構築する。
- 状態数を $n$ として、 $O(n Log)$

`int transition(int start, ll k)`
- 状態 $start$ から $k$ 回移動した状態を求める。
- $O(\log{k})$

---

# [Doubling (Monoid Applied)](./dbl2.hpp)

[参考](https://atcoder.jp/contests/ABC175/editorial/4722)

`Doubling<T, T(T, T) op, T() e, int Log>(vector<int> p, vector<T> v)`
- 各状態の 1 つ先の状態を記録した配列 $p$ と、各状態の値を記録した配列 $v$ からダブリングテーブルを構築する。

`T query(int start, ll k)`
- 状態 $start$ から $k$ 回移動した状態の値を求める。