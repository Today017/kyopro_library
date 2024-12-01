[top](../README.md)

# [Segment Tree](./segt.hpp)

`SegTree<Monoid>(int n)`
- サイズ $n$ の Segment Tree を構築する。
- モノイドが乗る。
- $O(n)$

`SegTree<Monoid>(vector<Monoid::Type> v)`
- 配列 $v$ から Segment Tree を構築する。

`void set(int i, Monoid::Type x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`Monoid::Type fold(int l, int r)`
- 区間 $[l, r)$ のモノイド積を返す。
- $O(\log{n})$

---

`RangeMin<T, T max_value>::Type`

`RangeMax<T, T min_value>::Type`

`RangeSum<T>::Type`