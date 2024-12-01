[top](../README.md)

# [Doubling](./dbl.hpp)

`Doubling<int Log>(vector<int> v)`
- 各状態の 1 つ先の状態を記録した配列 $v$ からダブリングテーブルを構築する。
- 状態数を $n$ として、 $O(n Log)$

`int next(int start, ll k)`
- 状態 $start$ から $k$ 回移動した状態を求める。
- $O(\log{k})$

---

# [Doubling (Monoid Applied)](./dbl2.hpp)

[参考](https://atcoder.jp/contests/ABC175/editorial/4722)

`Doubling<Monoid, int Log>(vector<int> p, vector<T> v)`
- 各状態の 1 つ先の状態を記録した配列 $p$ と、各状態での値を記録した配列 $v$ からダブリングテーブルを構築する。

`Monoid::Type fold(int start, ll k)`
- 状態 $start$ から $k$ 回移動したときのモノイド積を求める。