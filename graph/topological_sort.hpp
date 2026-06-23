#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/graph/graph.hpp"

/// @brief グラフ G をトポロジカルソートする
/// @note グラフにサイクルがある場合は空の配列を返す
/// @note O(V+E)
template <typename T>
vi TopologicalSort(const Graph<T>& G) {
    ii N = G.size();
    vi indeg(N);
    rep(i, N) for(auto e : G.next(i)) indeg[e.to]++;
    queue<ii> que;
    rep(i, N) if(indeg[i] == 0) que.push(i);
    vi ret;

    while(!que.empty()) {
        ii now = pick(que);
        for(auto e : G.next(now)) {
            indeg[e.to]--;
            if(indeg[e.to] == 0) que.push(e.to);
        }
        ret.push_back(now);
    }

    if(ret.size() != N) return {};
    return ret;
}
