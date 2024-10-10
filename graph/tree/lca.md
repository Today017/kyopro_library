[top](../../README.md)

# [Lowest Common Ancestor](./lca.hpp)

`LCA(vector<vector<int>> g, int root)`
- $root$ を根として、lcaのための前計算を行う。
- $O(n\log{n})$

`int lca(int u, int v)`
- 頂点 $u$, $v$ のLCAを返す。
- $O(\log{n})$

`int distance(int u, int v)`
- パス $u$, $v$ の長さを返す。
- $O(\log{n})$

`bool is_on_path(int u, int v, int x)`
- 頂点 $x$ がパス $u$, $v$ 上にあるかを返す。
- $O(\log{n})$

`int climb(int u, int d)`
- 頂点 $u$ から $d$ 回遡った祖先を返す。
- $0\le u < n$
- $O(\log{n})$

## [Edge Weighted](./lca_edge.hpp)

## [Vertex Weighted](./lca_vertex.hpp)