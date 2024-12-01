[top](../README.md)

# [Sparse Table](./spt.hpp)

`SparseTable<Band>(vector<T> v)`
- 配列 $v$ から Sparse Table を構築する。
- 冪等な半群が乗る。
- $O(n\log{n})$

`Band::Type fold(int l, int r)`
- 区間 $[l, r)$ の半群積を返す。
- $O(1)$