#include "../../../kyopro_library/template.hpp"

template <typename T, T (*op)(T, T), T (*e)()>
struct LcaEdgeQuery {
    LcaEdgeQuery(const vector<vector<pair<int, T>>> &g, int root = 0) {
        int n = g.size();
        int k = 1;
        while ((1 << k) < n) k++;
        dep = vector<int>(n, 0);
        parent = vector<vector<int>>(k, vector<int>(n, -1));
        dat = vector<vector<T>>(k, vector<T>(n, e()));
        dfs(g, root, -1);
        for (int i = 0; i + 1 < k; i++) {
            for (int j = 0; j < n; j++) {
                parent[i + 1][j] = parent[i][j] == -1 ? -1 : parent[i][parent[i][j]];
                dat[i + 1][j] = parent[i][j] == -1 ? e() : op(dat[i][j], dat[i][parent[i][j]]);
            }
        }
    }
    T query(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        ll ret = e();
        while (dep[u] < dep[v]) {
            int k = 0;
            while ((dep[v] - dep[u]) >= (1 << (k + 1))) k++;
            ret = op(ret, dat[k][v]);
            v = parent[k][v];
        }
        while (u != v) {
            int k = 0;
            while (parent[k + 1][u] != parent[k + 1][v]) k++;
            ret = op(ret, dat[k][u]);
            ret = op(ret, dat[k][v]);
            u = parent[k][u];
            v = parent[k][v];
        }
        return ret;
    }

private:
    vector<vector<int>> parent;
    vector<int> dep;
    vector<vector<T>> dat;
    void dfs(const vector<vector<pair<int, T>>> &g, int now, int pre) {
        parent[0][now] = pre;
        dep[now] = pre == -1 ? 0 : dep[pre] + 1;
        for (auto [nxt, cost] : g[now]) {
            if (nxt == pre) continue;
            dat[0][nxt] = cost;
            dfs(g, nxt, now);
        }
    }
};