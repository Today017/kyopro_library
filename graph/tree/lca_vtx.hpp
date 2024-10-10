#include "../../../kyopro_library/template.hpp"

template <typename T, T (*op)(T, T), T (*e)()>
struct LcaVertexQuery {
    LcaVertexQuery(const vector<vector<int>> &g, const vector<T> &v, int root) {
        int n = g.size();
        int k = 1;
        while ((1 << k) < n) k++;
        parent = vector<vector<int>>(k, vector<int>(n, -1));
        dep = vector<int>(n);
        dat = vector<vector<T>>(k, vector<T>(n, e()));
        dfs(g, v, root, -1, 0);
        for (int i = 0; i + 1 < k; i++) {
            for (int j = 0; j < n; j++) {
                parent[i + 1][j] = parent[i][j] == -1 ? -1 : parent[i][parent[i][j]];
                dat[i + 1][j] = parent[i][j] == -1 ? e() : op(dat[i][j], dat[i][parent[i][j]]);
            }
        }
    }
    T query(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        T ret = e();
        while (dep[u] < dep[v]) {
            int k = 0;
            while (dep[v] - dep[u] >= (1 << (k + 1))) k++;
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
        ret = op(ret, dat[0][u]);
        return ret;
    }

private:
    vector<vector<int>> parent;
    vector<int> dep;
    vector<vector<T>> dat;
    void dfs(const vector<vector<int>> &g, const vector<T> &v, int now, int par, int d) {
        dat[0][now] = v[now];
        parent[0][now] = par;
        dep[now] = d;
        for (int nxt : g[now]) {
            if (nxt == par) continue;
            dfs(g, v, nxt, now, d + 1);
        }
    }
};