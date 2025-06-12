#include"../../../kyopro_library/template.hpp"

/// @brief ワーシャルフロイド法
/// @brief 全頂点間の最短距離を求める
/// @note O(V^3)
void WarshallFloyd(vector<vector<ll>>& g) {
    int n=g.size();
    for(int k=0; k<n; k++) for(int i=0; i<n; i++) for(int j=0; j<n; j++) {
        chmin(g[i][j],g[i][k]+g[k][j]);
    }
}