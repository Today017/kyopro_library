[top](../README.md)

# [Doubling](./dbl.hpp)

`Doubling<int Log>(vector<int> a)`
- 各状態の 1 つ先の状態を記録した配列 $a$ からダブリングテーブルを構築する。
- 状態数を $n$ として、 $O(n Log)$

`int query(int start, ll k)`
- 状態 $start$ から $k$ 回移動した状態を求める。
- $O(\log{k})$
