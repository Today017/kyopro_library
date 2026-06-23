#pragma once
#include "../../../kyopro_library/template.hpp"
#include "../../../kyopro_library/graph/graph.hpp"

/// @brief ダイクストラ法
/// @brief 重み付きグラフ G に対し、頂点 start から各頂点までの最短距離を求める
/// @note O(E log V)
template <typename T>
vector<T> Dijkstra(const Graph<T>& G, int start = 0) {
    int N = G.size();
    vector<T> ret(N, inf<T>);
    ret[start] = 0;
    min_pq<PR<T, int>> pq;
    pq.push({0, start});

    while(!pq.empty()) {
        auto [tmp, now] = pq.top();
        pq.pop();
        if(ret[now] < tmp) continue;
        for(auto e : G.next(now))
            if(chmin(ret[e.to], ret[now] + e.w)) pq.push({ret[e.to], e.to});
    }

    return ret;
}
