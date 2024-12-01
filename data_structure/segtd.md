[top](../README.md)

# [Segment Tree Dual](./segtd.hpp)

`SegTreeDual<CommutativeOperator>(int n)`
- サイズ $n$ の 双対 Segment Tree を構築する。
- 作用素は可換である必要がある。
- $O(n)$

`CommutativeOperator::Type get(int i)`
- 位置 $i$ の要素を返す。
- $O(\log{n})$

`void apply(int l, int r, T x)`
- 区間 $[l, r)$ に対して $x$ を作用させる。
- $O(\log{n})$

---

`RangeAdd<T>::Type`

`RangeUpdate<T>::Type`