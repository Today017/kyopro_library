#include"../../../kyopro_library/template.hpp"

///@brief ワーシャルフロイド法
///@brief 全頂点間の最短距離を求める
///@note O(V^3)
void WarshallFloyd(vector<vector<ll>>& G) {
    //まあこのくらいならソラで書いたほうが
    int N=G.size();
    rep(k,N) rep(i,N) rep(j,N) chmin(G[i][j],G[i][k]+G[k][j]);
}