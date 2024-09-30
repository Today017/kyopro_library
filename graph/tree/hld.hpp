#include "../../../kyopro_library/template.hpp"

struct HLD {
    HLD(int n) {
        graph = vector<vector<int>>(n);
        sz = vector<int>(n);
        parent = vector<int>(n);
        depth = vector<int>(n);
        pos = vector<int>(n);
        head = vector<int>(n);
    }
    void add_edge(int a, int b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    HLD(const vector<vector<int>>& g) {
        int n = graph.size();
        this->graph = g;
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
    void update(int x, U& Update) { Update(x, pos[x]); }
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
    vector<vector<int>> graph;
    vector<int> sz, parent, depth, hld, pos, head;
    void dfs(int now, int a, int pre = -1) {
        pos[now] = hld.size();
        hld.push_back(now);
        head[now] = a;
        if (sz[now] == 1) return;
        int mx = 0;
        int mx_idx = 0;
        for (int nxt : graph[now]) {
            if (nxt == pre) continue;
            if (mx < sz[nxt]) {
                mx = sz[nxt];
                mx_idx = nxt;
            }
        }
        dfs(mx_idx, a, now);
        for (int nxt : graph[now]) {
            if (nxt == pre || nxt == mx_idx) continue;
            dfs(nxt, nxt, now);
        }
    }
    void dfs1(int now, int pre = -1) {
        int res = 1;
        for (int nxt : graph[now]) {
            if (nxt == pre) continue;
            dfs1(nxt, now);
            res += sz[nxt];
        }
        sz[now] = res;
    }
    void dfs2(int now, int pre = -1) {
        parent[now] = pre;
        for (int nxt : graph[now]) {
            if (nxt == pre) continue;
            depth[nxt] = depth[now] + 1;
            dfs2(nxt, now);
        }
    }
};
