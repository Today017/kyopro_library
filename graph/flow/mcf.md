[top](../../README.md)

# [Min Cost Flow](./mcf.cpp)

`min_cost_flow<Cap, Cost>(int n)`

`void add_edge(int u, int v, Cap cap, Cost cost)`
- 頂点 $u$ から $v$ へ 容量 $cap$, コスト $cost$ の辺を追加する。

`Cost get_min_cost_flow(int start, int goal, Cap flow)`
- 頂点 $start$ から $goal$ へ流量 $flow$ の最小費用流を流す。流せる場合はそのコスト、流せない場合は $inf$ を返す。
- Bellman Ford 法を用いている。
- $O(flow V E)$

---

```cpp
template <typename Cap, typename Cost>
struct min_cost_flow {
    min_cost_flow(int n) {
        this->n = n;
        G = vector<vector<tuple<int, Cap, Cost, int>>>(n);
    }
    void add_edge(int u, int v, Cap cap, Cost cost) {
        G[u].push_back(make_tuple(v, cap, cost, (int)G[v].size()));
        G[v].push_back(make_tuple(u, 0, -cost, (int)G[u].size() - 1));
    }
    Cost get_min_cost_flow(int start, int goal, Cap flow) {
        Cost ret = 0;
        while (flow > 0) {
            auto [dst, pre_vertex, pre_edge] = calculate_cost(start);
            if (dst[goal] == numeric_limits<Cost>::max()) {
                return numeric_limits<Cost>::max();
            }
            Cap now_flow = flow;
            int now_vertex = goal;
            while (now_vertex != start) {
                now_flow = min(now_flow, get<1>(G[pre_vertex[now_vertex]][pre_edge[now_vertex]]));
                now_vertex = pre_vertex[now_vertex];
            }
            ret += now_flow * dst[goal];
            flow -= now_flow;
            now_vertex = goal;
            while (now_vertex != start) {
                get<1>(G[pre_vertex[now_vertex]][pre_edge[now_vertex]]) -= now_flow;
                int rev = get<3>(G[pre_vertex[now_vertex]][pre_edge[now_vertex]]);
                get<1>(G[now_vertex][rev]) += now_flow;
                now_vertex = pre_vertex[now_vertex];
            }
        }
        return ret;
    }

private:
    int n;
    vector<vector<tuple<int, Cap, Cost, int>>> G;
    tuple<vector<Cost>, vector<int>, vector<int>> calculate_cost(int start) {
        vector<Cost> dst(n, numeric_limits<Cost>::max());
        vector<int> pre_vertex(n, 0), pre_edge(n, 0);
        dst[start] = 0;
        while (true) {
            bool update = false;
            for (int i = 0; i < n; i++) {
                if (dst[i] == numeric_limits<Cost>::max()) {
                    continue;
                }
                for (int j = 0; j < (int)G[i].size(); j++) {
                    auto [nxt, cap, cost, _] = G[i][j];
                    if (cap > 0 && dst[nxt] > dst[i] + cost) {
                        dst[nxt] = dst[i] + cost;
                        update = true;
                        pre_vertex[nxt] = i;
                        pre_edge[nxt] = j;
                    }
                }
            }
            if (!update) {
                break;
            }
        }
        return make_tuple(dst, pre_vertex, pre_edge);
    }
};

```