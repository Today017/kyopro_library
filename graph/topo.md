[top](../README.md)

# [Topological Sort](./topo.cpp)

`vector<int> topological_sort(const vector<vector<int>> &G)`
- グラフ $G$ に対して、トポロジカルソートを行う。
- グラフがDAGでない場合、配列のサイズが $V$ より小さくなる。
- $O(V + E)$

---

```cpp
vector<int> topological_sort(const vector<vector<int>> &G) {
    int n = G.size();
    vector<int> indeg(n);
    for (int i = 0; i < n; i++) {
        for (int nxt : G[i]) indeg[nxt]++;
    }
    queue<int> Q;
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) Q.push(i);
    }
    vector<int> ret;
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int nxt : G[now]) {
            indeg[nxt]--;
            if (indeg[nxt] == 0) Q.push(nxt);
        }
        ret.push_back(now);
    }
    return ret;
}

```