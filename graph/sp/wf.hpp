#include "../../../kyopro_library/template.hpp"

template <typename T>
void warshall_floyd(vector<vector<T>> &G, T inf = numeric_limits<T>::max()) {
    int n = G.size();
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (G[i][k] == inf || G[k][j] == inf) continue;
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
        }
    }
}

