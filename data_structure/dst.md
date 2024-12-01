[top](../README.md)

# [Disjoint Sparse Table](./dst.hpp)

`DisjointSparseTable<Semigroup>(vector<T> v)`
- 配列 $v$ から Disjoint Sparse Table を構築する。
- 半群が乗る。
- $O(n\log{n})$

`Semigroup::Type fold(int l, int r)`
- 区間 $[l, r)$ に対しての演算結果を返す。
- $O(1)$