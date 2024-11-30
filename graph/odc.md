[top](../README.md)

# [Offline Dynamic Connectivity](./odc.hpp)

`DynamicConnectiveity(int n,int q)`
- 頂点数 $n$ 、クエリ数 $q$ の Offline Dynamic Connectivity 問題を解く。

`void merge(int time, int u, int v)`
- 時間 $time$ に頂点 $u$, $v$ を連結する。

`void purge(int time, int u, int v)`
- 時間 $time$ に頂点 $u$, $v$ を削除する。

`void build()`

`void execute(F &f)`
- クエリ関数 f を処理する。
