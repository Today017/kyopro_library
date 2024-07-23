[top](../README.md)

# [Segment Tree](./segt.hpp)

`SegmentTree<T>(int n, F f, T e)`
- サイズ $n$ ,演算 $f$, 単位元 $e$ の Segment Tree を構築する。
- 集合 $T$, 演算 $f$, 単位元 $e$ が単位半群を為すことを要求する。
- $O(n)$

`void build(vector<T> a)`
- 配列 $a$ から Segment Tree を構築する。
- $O(n)$

`void set(int i, T x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`T query(int l, int r)`
- 区間 $[l, r)$ に対しての演算結果を返す。
- $O(\log{n})$

`T operator[int i]`
- 位置 $i$ の要素を返す。
- $O(1)$

`int size()`
- Segment Tree のサイズを返す。
- $O(1)$

---

`SegmentTree<T> RangeMinQuery(int n, T e)`
- Range Min Query 用の Segment Tree を返す。

`SegmentTree<T> RangeMaxQuery(int n, T e)`
- Range Max Query 用の Segment Tree を返す。

`SegmentTree<T> RangeSumQuery(int n)`
- Range Sum Query 用の Segment Tree を返す。