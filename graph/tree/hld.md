[top](../../README.md)

# [Heavy-Light Decomposition](./hld.cpp)

[解説](https://hcpc-hokudai.github.io/archive/graph_tree_001.pdf)

[使用例](https://atcoder.jp/contests/abc294/submissions/46419196)

`heavy_light_decomposition(int n)`
- $O(n)$

`heavy_light_decomposition(vector<vector<int>> G)`



`vector<int> start(int root)`
- 頂点 $root$ を根として木をHL分解する。分解後の木を返す。
- $0\le root<n$
- $O(n)$


`int lca(int u, int v)`
- 頂点 $u$, $v$ のLCA。
- $0\le u, v < n$
- $O(\log{n})$

`void update(int x, U Update)`
- 頂点 $x$ に対して、更新処理 $Update$ を適用する。
- $0\le x < n$
- $O(\log{n}f(n))$
- `Update(int x, int pos_x)`
	- 頂点 $x$, HLD後の列における $x$ の位置を $pos_x$ として、列の位置 $pos_x$ に対して更新処理を行う。
	- $O(f(n))$ とする。

`T query(int u, int v, Q Query, F f, T e)`
- パス $u$, $v$ に対して、取得処理 $Query$ を適用する。
- $0\le u, v < n$
- $O(\log{n}g(n))$
- `Query(int x, int y)`
	- HLD後の列の区間 $[x, y)$ に対して取得処理を行う。
	- $O(g(n))$ とする。
- `F(T a, T b)`
	- $Query$ による取得結果をまとめる演算を行う。RSQなら和、RMQならMin/Max演算を行う。
- `e`
	- 演算 $F$ の単位元。

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

---

```cpp
struct heavy_light_decomposition {
    heavy_light_decomposition(int n) {
        G = vector<int>(n);
        sz = vector<int>(n);
        parent = vector<int>(n);
        depth = vector<int>(n);
        pos = vector<int>(n);
        head = vector<int>(n);
    }
    void add_edge(int a, int b) {
        G[a].push_back(b);
        G[b].push_back(a);
    }
    heavy_light_decomposition(const vector<vector<int>>& G) {
        int n = G.size();
        this->G = G;
        sz = vector<int>(n);
        parent = vector<int>(n);
        depth = vector<int>(n);
        pos = vector<int>(n);
        head = vector<int>(n);
    }
    vector<int> hld_start(int root = 0) {
        dfs1(root);
        dfs2(root);
        dfs(root, root);
        return hld;
    }
    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                u = parent[head[u]];
            } else {
                v = parent[head[v]];
            }
        }
        return depth[u] < depth[v] ? u : v;
    }
    template <typename U>
    void update(int x, U& Update) {
        Update(x, pos[x]);
    }
    template <typename Q, typename F, typename T>
    T query(int u, int v, Q& Query, F& f, T e) {
        T ret = e;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]]) swap(u, v);
            ret = f(ret, Query(pos[head[u]], pos[u] + 1));
            u = parent[head[u]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        ret = f(ret, Query(pos[u], pos[v] + 1));
        return ret;
    }

private:
    vector<vector<int>> G;
    vector<int> sz, parent, depth, hld, pos, head;
    void dfs(int now, int a, int pre = -1) {
        pos[now] = hld.size();
        hld.push_back(now);
        head[now] = a;
        if (sz[now] == 1) return;
        int mx = 0;
        int mx_idx = 0;
        for (int nxt : G[now]) {
            if (nxt == pre) continue;
            if (mx < sz[nxt]) {
                mx = sz[nxt];
                mx_idx = nxt;
            }
        }
        dfs(mx_idx, a, now);
        for (int nxt : G[now]) {
            if (nxt == pre) continue;
            if (nxt == mx_idx) continue;
            dfs(nxt, nxt, now);
        }
    }
    void dfs1(int now, int pre = -1) {
        int res = 1;
        for (int nxt : G[now]) {
            if (nxt == pre) continue;
            dfs1(nxt, now);
            res += sz[nxt];
        }
        sz[now] = res;
    }
    void dfs2(int now, int pre = -1) {
        parent[now] = pre;
        for (int nxt : G[now]) {
            if (nxt == pre) continue;
            depth[nxt] = depth[now] + 1;
            dfs2(nxt, now);
        }
    }
};

```