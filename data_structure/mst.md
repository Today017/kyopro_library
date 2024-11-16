[top](../README.md)

# [Merge Sort Tree](./mst.hpp)

`MergeSortTree<T>(vector<T> a)`
- 配列 $a$ に対する Merge Sort Tree を構築する。

`int count_lt(int l, int r, T x)`
- $[l, r)$ に含まれる $x$ より小さい要素の個数を返す。
- $O(\log^2 n)$

`int count_le(int l, int r, T x)`

`int count_gt(int l, int r, T x)`

`int count_ge(int l, int r, T x)`

`T kth(int l, int r, int k)`
- $[l, r)$ に含まれる $k$ 番目に小さい要素を返す。
- $k$ は 1-indexed で与える。
- $O(\log^3 n)$

---