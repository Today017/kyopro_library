#include "../../../kyopro_library/template.hpp"
#include "../../../kyopro_library/graph/sp/dij.hpp"

pair<vector<int>, ll> treeDiameter(const vector<vector<pair<int, ll>>>& g) {
    vector<ll> dist = dijkstra(g);
    int s = max_element(dist.begin(), dist.end()) - dist.begin();
    dist = dijkstra(g, s);
    int t = max_element(dist.begin(), dist.end()) - dist.begin();
    vector<int> path;
    int now = t;
    while (now != s) {
        path.push_back(now);
        for (auto [nxt, cost] : g[now]) {
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

pair<vector<int>, ll> treeDiameter(const vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<pair<int, ll>>> h(n);
    for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
            h[i].push_back({j, 1});
        }
    }
    return treeDiameter(h);
}