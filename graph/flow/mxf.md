[top](../../README.md)

# [Max Flow](./mxf.hpp)

`MaxFlow<Cap>(int n)`

`void add_edge(int u, int v, Cap c)`
- 頂点 $u$ から $v$ へ 容量 $c$ の辺を追加する。

`Cap get(int start, int goal)`
- 頂点 $start$ から $goal$ への最大流を返す。
- Dinic 法を用いている。
- $O(V^2 E)$

## 特殊なグラフにおける計算量
全ての辺の容量が 1 であるとき、Dinic 法の計算量は、 $O(\min{\{V^{\frac{2}{3}},E^{\frac{1}{2}}\}})$