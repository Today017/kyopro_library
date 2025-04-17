#include "../../kyopro_library/template.hpp"

struct BridgeInfo {
    vector<pair<int, int>> bridge;
    vector<int> articulation;
};

BridgeInfo LowLink(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> ord(n, -1), low(n, -1), articulation;
    vector<bool> seen(n, false);
    vector<pair<int, int>> bridge;
    auto dfs = [&](auto&& dfs, int now, int pre, int& cnt) -> void {
        seen[now] = true;
        ord[now] = low[now] = cnt++;
        bool is_articulation = false;
        int child = 0;
        for (int nxt : g[now]) {
            if (!seen[nxt]) {
                child++;
                dfs(dfs, nxt, now, cnt);
                low[now] = min(low[now], low[nxt]);
                if (pre != -1 && ord[now] <= low[nxt]) is_articulation = true;
                if (ord[now] < low[nxt]) bridge.push_back(minmax(now, nxt));
            } else if (nxt != pre) {
                low[now] = min(low[now], ord[nxt]);
            }
        }
        if (pre == -1 && child > 1) is_articulation = true;
        if (is_articulation) articulation.push_back(now);
    };
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (!seen[i]) dfs(dfs, i, -1, cnt);
    }
    sort(bridge.begin(), bridge.end());
    sort(articulation.begin(), articulation.end());
    return {bridge, articulation};
}
