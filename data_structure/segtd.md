[top](../README.md)

# [Segment Tree Dual](./segtd.hpp)

`SegmentTreeDual<T>(int n, F f, T e)`
- サイズ $n$ ,演算 $f$, 単位元 $e$ の 双対 Segment Tree を構築する。
- $O(n)$

`void build(vector<T> a)`
- 配列 $a$ から 双対 Segment Tree を構築する。
- $O(n)$

`T operator[](int i)`
- 位置 $i$ の要素を返す。
- $O(\log{n})$

`void apply(int l, int r, T x)`
- 区間 $[l, r)$ に対して $x$ を作用させる。
- $O(\log{n})$

---

`SegmentTreeDual<T> RangeAddQuery(int n, T e)`
- Range Add Query 用の Segment Tree を返す。

`SegmentTreeDual<T> RangeUpdateQuery(int n, T e)`
- Range Update Query 用の Segment Tree を返す。