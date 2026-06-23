#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/graph/graph.hpp"

/// @brief 強連結成分分解の情報
template <typename T>
struct SccInfo {
    vector<vi> members;  ///< 各強連結成分の頂点
    Graph<T> graph_decomposed;  ///< 強連結成分による分解グラフ
    vi group;  ///< 各頂点の所属する強連結成分の番号
};

/// @brief グラフ G の強連結成分分解を行う
/// @brief { 各強連結成分の頂点, 強連結成分による分解グラフ, 各頂点の所属する強連結成分の番号 } を返す
/// @note O(V+E)
template <typename T>
SccInfo<T> SccDecomposition(const Graph<T>& G) {
    ii N = G.size();

    // 逆グラフを CSR 形式で構築（to のみ保持してキャッシュ効率を上げる）
    vi rhead(N + 1, 0);
    rep(i, N) for(const auto& e : G.next(i)) rhead[e.to + 1]++;
    rep(i, N) rhead[i + 1] += rhead[i];
    vi rnext(rhead[N]);
    {
        vi tmp(rhead.begin(), rhead.end());
        rep(i, N) for(const auto& e : G.next(i)) rnext[tmp[e.to]++] = i;
    }

    vi order;
    order.reserve(N);
    vi comp(N, -1);
    vector<char> seen(N, false);
    vi stk;
    stk.reserve(N);
    vi it(N, 0);

    // 1 回目: 反復 DFS で post-order を取る
    rep(s, N) if(!seen[s]) {
        seen[s] = true;
        stk.push_back(s);
        while(!stk.empty()) {
            ii u = stk.back();
            const auto& adj = G.next(u);
            if(it[u] < (ii)adj.size()) {
                ii v = adj[it[u]++].to;
                if(!seen[v]) {
                    seen[v] = true;
                    stk.push_back(v);
                }
            } else {
                order.push_back(u);
                stk.pop_back();
            }
        }
    }

    reverse(all(order));
    ii idx = 0;

    // 2 回目: 反復 DFS を逆グラフ上で行う
    fill(all(it), 0);
    for(ii s : order)
        if(comp[s] == -1) {
            comp[s] = idx;
            stk.push_back(s);
            while(!stk.empty()) {
                ii u = stk.back();
                ii deg = rhead[u + 1] - rhead[u];
                if(it[u] < deg) {
                    ii v = rnext[rhead[u] + it[u]++];
                    if(comp[v] == -1) {
                        comp[v] = idx;
                        stk.push_back(v);
                    }
                } else {
                    stk.pop_back();
                }
            }
            idx++;
        }

    ii nN = idx;
    vector<vi> ret(nN);
    rep(i, N) ret[comp[i]].push_back(i);
    vector<tuple<ii, ii, T>> edges;
    rep(i, N) for(const auto& e : G.next(i)) if(comp[i] != comp[e.to]) edges.push_back({comp[i], comp[e.to], e.w});
    sort(all(edges));
    edges.erase(unique(all(edges)), edges.end());
    Graph<T> ret2(nN);
    for(const auto& [from, to, w] : edges) ret2.add_edge(from, to, w);

    return {ret, ret2, comp};
}
