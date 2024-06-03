[top](../README.md)

# [Set Interface](./set.hpp)

`my_set<T>(T not_found)`
- `not_found` は所望の値が見つからなかった場合に返す値として定義する。デフォルトは `INFL` 。

`T min()`
- 最小値を返す。
- $O(1)$

`T max()`
- 最大値を返す。
- $O(1)$

`bool contains(T x)`
- $x$ が含まれているかどうかを返す。
- $O(\log N)$

`T gt(T x)`
- $x$ より大きい最小の値を返す。
- $O(\log N)$

`T lt(T x)`
- $x$ より小さい最大の値を返す。
- $O(\log N)$

`T ge(T x)`
- $x$ 以上で最小の値を返す。
- $O(\log N)$

`T le(T x)`
- $x$ 以下で最大の値を返す。
- $O(\log N)$

`bool discard(T x)`
- $x$ を削除する。含まれていない場合は `false` を返す。
- $O(\log N)$