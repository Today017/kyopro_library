[top](../README.md)

# [Sorted Tree](./tree.hpp)

`tree<T>`
- 順序付き集合を管理するデータ構造。

`T max()`
- 最大値を求める。

`T min()`
- 最小値を求める。

`T pop_max()`
- 最大値を返し、削除する。

`T pop_min()`
- 最小値を返し、削除する。

`bool discard(T x)`
- 要素 $x$ を削除する。存在しない場合は `false` を返す。

`T gt(T x)`
- $x$ より大きい最小の値を返す。存在しない場合は `NULL` を返す。

`T ge(T x)`
- $x$ 以上の最小の値を返す。存在しない場合は `NULL` を返す。

`T lt(T x)`
- $x$ 未満最大の値を返す。存在しない場合は `NULL` を返す。

`T le(T x)`
- $x$ 以下最大の値を返す。存在しない場合は `NULL` を返す。

`T kth_min(int k)`
- $k$ 番目に小さい値を返す。`0-indexed` であることに注意。

`T kth_max(int k)`
- $k$ 番目に大きい値を返す。

`int count_lt(T x)`
- $x$ 未満の要素の個数を返す。

`int count_le(T x)`
- $x$ 以下の要素の個数を返す。

`int count_gt(T x)`
- $x$ より大きい要素の個数を返す。

`int count_gt(T x)`
- $x$ 以上の要素の個数を返す。

`bool contains(T x)`
- $x$ が含まれているか否かを返す。