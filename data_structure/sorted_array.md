[top](../README.md)

# [Sorted Array](./sorted_arra.hpp)

`soted_array<T>(vector<T> a, T not_found = -1)`
- $a$ を Sorted Array に変換する。

`bool find(T x)`
- $x$ が $a$ に含まれるかどうかを返す。
- $O(\log N)$

`T max()`
- $a$ の最大値を返す。
- $O(1)$

`T min()`
- $a$ の最小値を返す。
- $O(1)$

`T gt(T x)`
- $x$ より大きい最小の値を返す。存在しない場合は `not_found` を返す。
- $O(\log N)$

`T ge(T x)`
- $x$ 以上の最小の値を返す。存在しない場合は `not_found` を返す。
- $O(\log N)$

`T lt(T x)`
- $x$ より小さい最大の値を返す。存在しない場合は `not_found` を返す。
- $O(\log N)$

`T le(T x)`
- $x$ 以下の最大の値を返す。存在しない場合は `not_found` を返す。
- $O(\log N)$

`T kth_min(int k)`
- $a$ の $k$ 番目に小さい要素を返す。存在しない場合は `not_found` を返す。
- $O(1)$

`T kth_min_unique(int k)`
- $a$ を集合として見たときの $k$ 番目に小さい要素を返す。存在しない場合は `not_found` を返す。
- $O(1)$

`T kth_max(int k)`
- $a$ の $k$ 番目に大きい要素を返す。存在しない場合は `not_found` を返す。
- $O(1)$

`T kth_max_unique(int k)`
- $a$ を集合として見たときの $k$ 番目に大きい要素を返す。存在しない場合は `not_found` を返す。
- $O(1)$

`int count_gt(T x)`
- $x$ より大きい要素の数を返す。
- $O(\log N)$

`int count_ge(T x)`
- $x$ 以上の要素の数を返す。
- $O(\log N)$

`int count_lt(T x)`
- $x$ より小さい要素の数を返す。
- $O(\log N)$

`int count_le(T x)`
- $x$ 以下の要素の数を返す。
- $O(\log N)$

`int count_gt_unique(T x)`
- $a$ を集合として見たときの $x$ より大きい要素の数を返す。 
- $O(\log N)$

`int count_ge_unique(T x)`
- $a$ を集合として見たときの $x$ 以上の要素の数を返す。
- $O(\log N)$

`int count_lt_unique(T x)`
- $a$ を集合として見たときの $x$ より小さい要素の数を返す。
- $O(\log N)$

`int count_le_unique(T x)`
- $a$ を集合として見たときの $x$ 以下の要素の数を返す。
- $O(\log N)$

`int count(T x)`
- $x$ と等しい要素の数を返す。
- $O(\log N)$

`int index(T x)`
- $x$ が $a$ に含まれる場合、そのインデックスを返す。含まれない場合は $-1$ を返す。
- $O(\log N)$