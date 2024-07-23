[top](../README.md)

# [Segment Tree Lazy](./segtlz.hpp)

`SegmentTreeLazy<T, U>(int n, F f, G g, H h, T et, U eu)`
- 遅延評価 Segment Tree を構築する。

`void build(vector<T> a)`
- 配列 $a$ から 遅延評価 Segment Tree を構築する。
- $O(n)$

`void set(int i, T x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`T query(int l, int r)`
- 区間 $[l, r)$ に対しての演算結果を返す。
- $O(\log{n})$

`void apply(int l, int r, U x)`
- 区間 $[l, r)$ に対して $x$ を作用させる。
- $O(\log{n})$

`T operator[int i]`
- 位置 $i$ の要素を返す。
- $O(\log{n})$
- 遅延伝播を検査する必要があるため。

`int size()`
- Segment Tree のサイズを返す。
- $O(1)$

---

`SegmentTreeLazy<T> RangeAddRangeMin(int n, T max)`
- Range Add Range Min Query 用の 遅延評価 Segment Tree を返す。

`SegmentTreeLazy<T> RangeAddRangeMax(int n, T min)`
- Range Add Range Max Query 用の 遅延評価 Segment Tree を返す。

`SegmentTreeLazy<T> RangeAddRangeSum(int n)`
- Range Add Range Sum Query 用の 遅延評価 Segment Tree を返す。

`SegmentTreeLazy<T> RangeUpdateRangeMin(int n, T max, T not_exist)`
- Range Update Range Min Query 用の 遅延評価 Segment Tree を返す。

`SegmentTreeLazy<T> RangeUpdateRangeMax(int n, T min, T not_exist)`
- Range Update Range Max Query 用の 遅延評価 Segment Tree を返す。

`SegmentTreeLazy<T> RangeUpdateRangeSum(int n, T not_exist)`
- Range Update Range Sum Query 用の 遅延評価 Segment Tree を返す。