[top](../README.md)

# [Disjoint Set Union (Potentialized)](./dsup.hpp)

`DsuPotentialized<Group>(int n)`
- 重み付き DSU。
- 群が乗る。

`bool merge(int x, int y, Group w)`
- 頂点 $x$, $y$ を連結する。このとき、 $W_x = W_y \cdot w$ とする。
- $O(\alpha(n))$

`Group::Type diff(int x, int y)`
- ${W_y}^{-1} \cdot W_x$ を返す。
- $O(1)$