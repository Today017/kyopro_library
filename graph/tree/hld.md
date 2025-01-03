[top](../../README.md)

# [Heavy-Light Decomposition](./hld.hpp)

[解説](https://hcpc-hokudai.github.io/archive/graph_tree_001.pdf)

[使用例](https://atcoder.jp/contests/abc294/submissions/46419196)

`HLD(int n)`

`HLD(vector<vector<int>> g)`


`vector<int> build(int root)`
- 頂点 $root$ を根として木を列に HL 分解する。分解後の木を返す。
- $O(n)$


`int lca(int u, int v)`
- 頂点 $u$, $v$ の LCA を返す。
- $O(\log{n})$

`int at(int v)`
- 頂点 $v$ の HL 分解後の位置を返す。
- $O(1)$

`vector<tuple<bool, int, int>> path(int u, int v)`
- 頂点 $u$, $v$ を結ぶパスを HL 分解後の辺の列にして返す。
- `[flag, l, r]` として、以下を表す。
	- `[l, r]` : HL 分解後の頂点列 ($[l, r]$)
	- `flag = true` のとき、 $[l, r]$ は $v$ から $u$ への向き
	- `flag = false` のとき、 $[l, r]$ は $u$ から $v$ への向き

---

#### メンバ
`vector<int> sz`
- 頂点の部分木の大きさ

`vector<int> parent`
- 頂点の親

`vector<int> depth`
- 頂点の深さ

`vector<int> hld`
- HLD結果としての配列

`vector<int> pos`
- `hld`における頂点の位置

`vector<int> head`
- 頂点の属する連結成分の最も浅い頂点