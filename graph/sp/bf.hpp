#include "../../../kyopro_library/template.hpp"

pair<bool, vector<ll>> bellmanFord(const vector<vector<pair<int, ll>>> &g, int start) {
    int n = g.size();
    vector<ll> dst(n, INFL);
    dst[start] = 0;
    int i = 0;
    for (; i < n; i++) {
        bool update = false;
        for (int j = 0; j < n; j++) {
            for (auto [nxt, cost] : g[j]) {
                if (dst[j] != INFL && dst[j] + cost < dst[nxt]) {
                    dst[nxt] = dst[j] + cost;
                    update = true;
                }
            }
        }
        if (!update) {
            break;
        }
    }
    return {i == n, dst};
}