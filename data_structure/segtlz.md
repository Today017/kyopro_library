[top](../README.md)

# [Segment Tree Lazy](./segtlz.hpp)

`SegTreeLazy<Monoid, Operator, mapping>(int n)`
- サイズ $n$ の遅延評価 Segment Tree を構築する。

`void set(int i, Monoid::Type x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`Monoid::Type fold(int l, int r)`
- 区間 $[l, r)$ に対してのモノイド積を返す。
- $O(\log{n})$

`void apply(int l, int r, Operator::Type x)`
- 区間 $[l, r)$ に対して $x$ を作用させる。
- $O(\log{n})$

---

`RangeUpdateRangeMin<T, T max_value, T not_exist>::Type`

`RangeUpdateRangeMax<T, T min_value, T not_exist>::Type`

`RangeUpdateRangeSum<T, T not_exist>::Type`

`RangeAddRangeMin<T, T max_value>::Type`

`RangeAddRangeMax<T, T min_value>::Type`

`RangeAddRangeSum<T>::Type`