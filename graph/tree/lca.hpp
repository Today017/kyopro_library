#include "../../../kyopro_library/template.hpp"

struct LCA {
    LCA(vector<vector<int>> &g, int root = 0) {
        int n = g.size();
        int k = 1;
        while ((1 << k) < n) k++;
        par.assign(k, vector<int>(n, -1));
        dst.assign(n, -1);
        dfs(g, root, -1, 0);
        for (int i = 0; i + 1 < k; i++) {
            for (int j = 0; j < n; j++) {
                if (par[i][j] < 0) {
                    par[i + 1][j] = -1;
                } else {
                    par[i + 1][j] = par[i][par[i][j]];
                }
            }
        }
    }
    int lca(int u, int v) {
        if (dst[u] < dst[v]) swap(u, v);
        int k = par.size();
        for (int i = 0; i < k; i++) {
            if ((dst[u] - dst[v]) >> i & 1) u = par[i][u];
        }
        if (u == v) return u;
        for (int i = k - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) {
                u = par[i][u];
                v = par[i][v];
            }
        }
        return par[0][u];
    }
    int distance(int u, int v) {return dst[u] + dst[v] - 2 * dst[lca(u, v)];}
    bool is_on_path(int u, int v, int x) {
        return distance(u, x) + distance(x, v) == distance(u, v);
    }
    int climb(int u, int d) {
        int k = par.size();
        for (int i = k - 1; i >= 0; i--) {
            if (d >> i & 1) u = par[i][u];
        }
        return u;
    }

private:
    vector<vector<int>> par;
    vector<int> dst;
    void dfs(vector<vector<int>> &g, int now, int pre, int tmp) {
        par[0][now] = pre;
        dst[now] = tmp;
        for (int nxt : g[now]) {
            if (nxt != pre) dfs(g, nxt, now, tmp + 1);
        }
    }
};
