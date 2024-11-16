[top](../README.md)

# [Disjoint Set Union (Merging)](./dsup.hpp)

`DsuPotentialized<CommutativeSemiGroup, op>(int n, vector<CommutativeSemiGroup> v)`
- 頂点に値を載せて merge していく DSU。
- 可換半群が載る。

`void merge(int x, int y, Group w)`
- 頂点 $x$, $y$ を連結する。このとき、新しい親を $x$ として、 $V_x = V_x \cdot V_y$ とする。
- $O(\alpha(n))$

`CommutativeSemiGroup get(int x)`
- 頂点 $x$ の値を返す。
- $O(\alpha(n))$