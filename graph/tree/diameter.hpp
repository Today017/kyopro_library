#include "../../../kyopro_library/template.hpp"
#include "../../../kyopro_library/graph/sp/dij.hpp"

pair<vector<int>, ll> tree_diameter_path(const vector<vector<pair<int, ll>>>& G) {
    vector<ll> dist = dijkstra(G);
    int s = max_element(dist.begin(), dist.end()) - dist.begin();
    dist = dijkstra(G, s);
    int t = max_element(dist.begin(), dist.end()) - dist.begin();
    vector<int> path;
    int now = t;
    while (now != s) {
        path.push_back(now);
        for (auto [nxt, cost] : G[now]) {
            if (dist[now] == dist[nxt] + cost) {
                now = nxt;
                break;
            }
        }
    }
    path.push_back(s);
    ll diameter = dist[t];
    return {path, diameter};
}

pair<vector<int>, ll> tree_diameter_path(const vector<vector<int>>& G) {
    int n = G.size();
    vector<vector<pair<int, ll>>> H(n);
    for (int i = 0; i < n; i++) {
        for (int j : G[i]) {
            H[i].push_back({j, 1});
        }
    }
    return tree_diameter_path(H);
}