#include "../../kyopro_library/template.hpp"

struct SCC {
    vector<vector<int>> members, graph_decomposed;
    vector<int> group;
};

SCC sccDecomposition(const vector<vector<int>> &g) {
    int n = g.size();
    vector<vector<int>> g2(n);
    for (int i = 0; i < n; i++) {
        for (int nxt : g[i]) {
            g2[nxt].push_back(i);
        }
    }
    vector<int> order(n), component(n, -1);
    vector<bool> vst(n);
    auto f = [&](auto f, int now) -> void {
        vst[now] = true;
        for (int nxt : g[now]) {
            if (!vst[nxt]) {
                f(f, nxt);
            }
        }
        order.push_back(now);
    };
    auto f2 = [&](auto f2, int now, int idx) -> void {
        component[now] = idx;
        for (int nxt : g2[now]) {
            if (component[nxt] == -1) {
                f2(f2, nxt, idx);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!vst[i]) {
            f(f, i);
        }
    }
    int idx = 0;
    reverse(order.begin(), order.end());
    for (int now : order) {
        if (component[now] == -1) {
            f2(f2, now, idx);
            idx++;
        }
    }
    int n_n = *max_element(component.begin(), component.end()) + 1;
    vector<vector<int>> ret(n_n);
    for (int i = 0; i < n; i++) {
        ret[component[i]].push_back(i);
    }
    vector<vector<int>> ret2(n_n);
    for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
            if (component[i] != component[j]) {
                ret2[component[i]].push_back(component[j]);
            }
        }
    }
    for (int i = 0; i < n_n; i++) {
        sort(ret2[i].begin(), ret2[i].end());
        ret2[i].erase(unique(ret2[i].begin(), ret2[i].end()), ret2[i].end());
    }
    return {ret, ret2, component};
}
