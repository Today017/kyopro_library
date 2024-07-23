#include "../../../kyopro_library/template.hpp"

void warshallFloyd(vector<vector<ll>> &g) {
    int n = g.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][k] == INFL || g[k][j] == INFL) continue;
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
}

