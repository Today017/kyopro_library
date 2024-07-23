[top](../README.md)

# [Topological Sort](./toposort.hpp)

`vector<int> TopologicalSort(const vector<vector<int>> &g)`
- グラフ $g$ に対して、トポロジカルソートを行う。
- グラフが DAG でない場合、配列のサイズが $V$ より小さくなる。
- $O(V + E)$