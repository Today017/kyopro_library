#pragma once
#include "../../../kyopro_library/template.hpp"
#include "../../../kyopro_library/graph/graph.hpp"

/// @brief 01BFS
template <typename T>
V<T> BFS01(const Graph<T>& G, int start) {
    int N = G.size();
    vector<T> ret(N, inf<T>);
    ret[start] = 0;
    deque<pair<T, int>> dq;
    dq.push_front({0, start});

    while(!dq.empty()) {
        auto [tmp, now] = dq.front();
        dq.pop_front();
        if(ret[now] < tmp) continue;
        for(auto e : G.next(now)) {
            if(chmin(ret[e.to], ret[now] + e.w)) {
                if(e.w == 0) dq.push_front({ret[e.to], e.to});
                else dq.push_back({ret[e.to], e.to});
            }
        }
    }

    return ret;
}
