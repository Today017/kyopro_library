[top](../README.md)

# [Disjoint Set Union (Potentialized)](./dsup.hpp)

`DsuPotentialized<Group, op, e, inv>(int n)`
- 重み付き DSU。
- `Group` は群(非可換でもよい)、 `op` は群の演算、`e` は単位元、`inv` は逆元を返す関数とする。

`void unite(int x, int y, Group w)`
- 頂点 $x$, $y$ を連結する。このとき、 $W_x = W_y \cdot w$ とする。
- $O(\alpha(n))$

`Group diff(int x, int y)`
- ${W_y}^{-1} \cdot W_x$ を返す。
- $O(1)$