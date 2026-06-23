#pragma once
#include "../../../kyopro_library/template.hpp"

/// @brief LCA
/// @ref verify: https://onlinejudge.u-aizu.ac.jp/status/users/Today03/submissions/1/GRL_5_C/judge/10572843/C++17
struct LCA {
    LCA() = default;

    LCA(const vector<vi>& g, ii root = 0) {
        ii n = g.size(), k = 1;
        while((1 << k) < n) k++;
        par = vector<vi>(k, vi(n, -1)), dep = vi(n);
        dfs(g, root, -1);
        rep(i, k - 1) rep(j, n) par[i + 1][j] = (par[i][j] == -1 ? -1 : par[i][par[i][j]]);
    }

    ii lca(ii u, ii v) {
        if(dep[u] < dep[v]) swap(u, v);
        ii k = par.size();
        rep(i, k) if((dep[u] - dep[v]) >> i & 1) u = par[i][u];
        if(u == v) return u;
        for(ii i = k - 1; i >= 0; i--)
            if(par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        return par[0][u];
    }

    ii distance(ii u, ii v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

    bool is_on_path(ii u, ii v, ii x) { return distance(u, x) + distance(x, v) == distance(u, v); }

    ii climb(ii u, ii d) {
        ii k = par.size();
        for(ii i = k - 1; i >= 0; i--)
            if(d >> i & 1) u = par[i][u];
        return u;
    }

    vector<vi> par;
    vi dep;

private:
    void dfs(const vector<vi>& g, ii now, ii pre) {
        par[0][now] = pre;
        dep[now] = (pre == -1 ? 0 : dep[pre] + 1);
        for(ii nxt : g[now])
            if(nxt != pre) dfs(g, nxt, now);
    }
};

// https://atcoder.jp/contests/abc460/submissions/76302152
struct FastLCA {
    ii n;
    vi depth;
    vi first_visit;
    // st[i][j] : 長さ 2^i の区間における {深さ, 頂点番号} の最小値
    vector<vector<pair<ii, ii>>> st;
    vi log_table;
    FastLCA() = default;

    // adj は 0-indexed の隣接リスト、root は根の頂点番号
    FastLCA(const vector<vi>& adj, ii root = 0) {
        n = adj.size();
        depth.assign(n, 0);
        first_visit.assign(n, -1);
        vector<pair<ii, ii>> euler_tour;
        euler_tour.reserve(2 * n);

        // オイラーツアーの構築
        auto dfs = [&](auto& self, ii u, ii p, ii d) -> void {
            first_visit[u] = euler_tour.size();
            euler_tour.push_back({d, u});
            depth[u] = d;
            for(ii v : adj[u]) {
                if(v != p) {
                    self(self, v, u, d + 1);
                    // 子から戻ってきたときにも追加
                    euler_tour.push_back({d, u});
                }
            }
        };
        dfs(dfs, root, -1, 0);

        ii m = euler_tour.size();

        // Sparse Table 用の対数テーブル事前計算
        log_table.assign(m + 1, 0);
        for(ii i = 2; i <= m; i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }

        // Sparse Table の構築
        ii k = log_table[m] + 1;
        st.assign(k, vector<pair<ii, ii>>(m));
        for(ii i = 0; i < m; i++) {
            st[0][i] = euler_tour[i];
        }

        for(ii j = 1; j < k; j++) {
            for(ii i = 0; i + (1 << j) <= m; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // u と v の LCA を O(1) で取得
    ii lca(ii u, ii v) const {
        ii l = first_visit[u];
        ii r = first_visit[v];
        if(l > r) swap(l, r);

        ii j = log_table[r - l + 1];
        // 2つの区間の最小値を取る (区間は被っていてもよい性質を利用)
        return min(st[j][l], st[j][r - (1 << j) + 1]).second;
    }

    // u と v の距離を O(1) で取得
    ii dist(ii u, ii v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};
