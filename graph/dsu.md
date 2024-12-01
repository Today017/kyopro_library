[top](../README.md)

# [Disjoint Set Union](./dsu.hpp)

`DSU(int n)`

`int find(int x)`
- 頂点 $x$ を含む連結成分の代表元を返す。
- $O(\alpha(n))$

`bool merge(int x, int y)`
- 頂点 $x$, $y$ を連結し、`true` を返す。
- 既に連結されている場合は `false` を返す。
- $O(\alpha(n))$

`int size(int x)`
- 頂点 $x$ を含む連結成分のサイズを返す。
- $O(1)$

`bool same(int x, int y)`
- 頂点の組 $(x, y)$ が連結であるか否かを返す。
- $O(\alpha(n))$

`int count()`
- 連結成分の数を返す。
- $O(1)$

`vector<vector<int>> groups`
- 連結成分ごとに所属する頂点を返す。
- $O(N)$
