[top](../README.md)

# [SCC Decomposition](./scc.cpp)

`auto scc_decomposition(const vector<vector<int>> G)`
- グラフ $G$ に対して強連結成分分解をする。
- $($ 各連結成分に属する頂点, SCC 後のグラフ, 各頂点の属する連結成分 $)$ を返す。
- $O(V + E)$

---

```cpp
tuple<vector<vector<int>>, vector<vector<int>>, vector<int>> scc_decomposition(const vector<vector<int>> &G) {
    int n = G.size();
    vector<vector<int>> G2(n);
    for (int i = 0; i < n; i++) {
        for (int nxt : G[i]) {
            G2[nxt].push_back(i);
        }
    }
    vector<int> order(n), component(n, -1);
    vector<bool> vst(n);
    auto F = [&](auto F, int now) -> void {
        vst[now] = true;
        for (int nxt : G[now]) {
            if (!vst[nxt]) {
                F(F, nxt);
            }
        }
        order.push_back(now);
    };
    auto F2 = [&](auto F2, int now, int idx) -> void {
        component[now] = idx;
        for (int nxt : G2[now]) {
            if (component[nxt] == -1) {
                F2(F2, nxt, idx);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!vst[i]) {
            F(F, i);
        }
    }
    int idx = 0;
    reverse(order.begin(), order.end());
    for (int now : order) {
        if (component[now] == -1) {
            F2(F2, now, idx);
            idx++;
        }
    }
    int n_n = *max_element(component.begin(), component.end()) + 1;
    vector<vector<int>> ret(n_n);
    for (int i = 0; i < n; i++) {
        ret[component[i]].push_back(i);
    }
    vector<vector<int>> ret2(n_n);
    for (int i = 0; i < n; i++) {
        for (int j : G[i]) {
            if (component[i] != component[j]) {
                ret2[component[i]].push_back(component[j]);
            }
        }
    }
    for (int i = 0; i < n_n; i++) {
        sort(ret2[i].begin(), ret2[i].end());
        ret2[i].erase(unique(ret2[i].begin(), ret2[i].end()), ret2[i].end());
    }
    return make_tuple(ret, ret2, component);
}

```
