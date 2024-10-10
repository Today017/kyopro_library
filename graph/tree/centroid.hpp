#include "../../../kyopro_library/template.hpp"

int getCentroid(const vector<vector<int>>& g, int root, vector<bool>& seen, vector<int>& sz) {
    int n = g.size();
    if (sz.empty()) sz = vector<int>(n);
    if (seen.empty()) seen = vector<bool>(n, false);
    auto dfs = [&](auto dfs, int now, int pre) -> int {
        sz[now] = 1;
        for (int nxt : g[now]) {
            if (nxt == pre || seen[nxt]) continue;
            sz[now] += dfs(dfs, nxt, now);
        }
        return sz[now];
    };
    int total = dfs(dfs, root, -1);
    int centroid = root;
    auto dfs2 = [&](auto dfs2, int now, int pre) -> void {
        bool ok = (total - sz[now]) * 2 <= total;
        for (int nxt : g[now]) {
            if (nxt == pre || seen[nxt]) continue;
            dfs2(dfs2, nxt, now);
            if (sz[nxt] * 2 > total) ok = false;
        }
        if (ok) centroid = now;
    };
    dfs2(dfs2, root, -1);
    return centroid;
}