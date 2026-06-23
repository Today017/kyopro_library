#pragma once
#include "../../../kyopro_library/template.hpp"

/**
 * @brief 重心分解
 * @param seen 探索済みフラグ
 * @param sz 各頂点の部分木のサイズ
 *
 * ```cpp
 * vi sz(N);
 * vector<bool> seen(N);
 *
 * auto centroid_decomposition = [&](auto self, int root) -> void {
 *     int centroid = TreeCentroid(G, root, seen, sz);
 *     seen[centroid] = true;
 *
 *     // ここに処理を書く
 *
 *     for (int nxt : G[centroid]) {
 *         if (seen[nxt]) continue;
 *         self(self, nxt);
 *     }
 * };
 * centroid_decomposition(centroid_decomposition, 0);
 * ```
 */
int TreeCentroid(const vector<vi>& G, int root, vi& seen, vi& sz) {
    int N = G.size();
    if(sz.empty()) sz = vi(N);
    if(seen.empty()) seen = vi(N, false);

    auto dfs = [&](auto dfs, int now, int pre) -> int {
        sz[now] = 1;
        for(int nxt : G[now]) {
            if(nxt == pre || seen[nxt]) continue;
            sz[now] += dfs(dfs, nxt, now);
        }
        return sz[now];
    };

    int total = dfs(dfs, root, -1);
    int centroid = root;

    auto dfs2 = [&](auto dfs2, int now, int pre) -> void {
        bool ok = (total - sz[now]) * 2 <= total;
        for(int nxt : G[now]) {
            if(nxt == pre || seen[nxt]) continue;
            dfs2(dfs2, nxt, now);
            if(sz[nxt] * 2 > total) ok = false;
        }
        if(ok) centroid = now;
    };
    dfs2(dfs2, root, -1);

    return centroid;
}