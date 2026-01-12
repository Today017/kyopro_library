#include"../../../kyopro_library/template.hpp"

///@brief ワーシャルフロイド法
///@brief 全頂点間の最短距離を求める
///@note O(V^3)
void WarshallFloyd(vector<vector<ll>>& g) {
    int n=g.size();
    rep(k,n) rep(i,n) rep(j,n) {
        chmin(g[i][j],g[i][k]+g[k][j]);
    }
}