[top](../README.md)

# [Convex Hull Trick](./cht.hpp)

`convex_hull_trick<T, MIN>`
- 直線を管理し、クエリに対して最小値、または最大値を求める。

`add(T a, T b)`
- 直線 $y = ax + b$ を追加する。
- 直線集合のサイズを $N$ として $O(\log N)$

`get(T x)`
- $x$ における最小値、または最大値を求める。
- $O(\log^2 N)$
