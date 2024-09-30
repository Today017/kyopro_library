#include "../../../kyopro_library/template.hpp"

vector<int> treeCentroid(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> ret, sz(n);
    auto dfs = [&](auto &&dfs, int now, int pre) -> void {
        sz[now] = 1;
        bool is_centroid = true;
        for (int nxt : g[now]) {
            if (nxt == pre) continue;
            dfs(dfs, nxt, now);
            sz[now] += sz[nxt];
            if (sz[nxt] > n / 2) is_centroid = false;
        }
        if (n - sz[now] > n / 2) is_centroid = false;
        if (is_centroid) ret.push_back(now);
    };
    dfs(dfs, 0, -1);
    return ret;
}