#include"../../../kyopro_library/template.hpp"

/// @brief ワーシャルフロイド法
/// @brief 全頂点間の最短距離を求める
/// @note O(V^3)
void WarshallFloyd(VVL&g){
	int n=g.size();
	REP(k,n)REP(i,n)REP(j,n) chmin(g[i][j],g[i][k]+g[k][j]);
}