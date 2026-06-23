#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/graph/graph.hpp"

/// @brief 橋と関節点の情報
struct BridgeInfo {
    vector<pair<ii, ii>> bridge;  ///< 橋
    vi articulation;  ///< 関節点
};

/// @brief Low Link のアルゴリズムによりグラフGの橋と関節点を求める
/// @note O(V+E)
// BridgeInfo LowLink(const vector<vi>& g) {
template <typename T>
BridgeInfo LowLink(const Graph<T>& G) {
    ii N = G.size();
    vi ord(N, -1), low(N, -1), articulation, seen(N, false);
    vector<pair<ii, ii>> bridge;

    auto dfs = [&](auto&& dfs, ii now, ii pre, ii& cnt) -> void {
        seen[now] = true;
        ord[now] = low[now] = cnt++;
        bool is_articulation = false;
        ii child = 0;
        for(auto e : G.next(now)) {
            if(!seen[e.to]) {
                child++;
                dfs(dfs, e.to, now, cnt);
                low[now] = min(low[now], low[e.to]);
                if(pre != -1 && ord[now] <= low[e.to]) is_articulation = true;
                if(ord[now] < low[e.to]) bridge.push_back(minmax(now, e.to));
            } else if(e.to != pre) low[now] = min(low[now], ord[e.to]);
        }
        if(pre == -1 && child > 1) is_articulation = true;
        if(is_articulation) articulation.push_back(now);
    };

    ii cnt = 0;
    rep(i, N) if(!seen[i]) dfs(dfs, i, -1, cnt);
    sort(all(bridge));
    sort(all(articulation));
    return {bridge, articulation};
}
