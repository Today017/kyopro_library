[top](../README.md)

# [Disjoint Set Union (Merging)](./dsup.hpp)

`DsuMerging<CommutativeSemigroup, op>(int n, vector<CommutativeSemigroup> v)`
- 頂点に値を載せて merge していく DSU。
- 可換半群が載る。

`bool merge(int x, int y)`
- 頂点 $x$, $y$ を連結する。このとき、新しい親を $x$ として、 $V_x = V_x \cdot V_y$ とする。
- $O(\alpha(n))$

`CommutativeSemigroup::Type get(int x)`
- 頂点 $x$ の含まれる連結成分の半群積を返す。
- $O(\alpha(n))$