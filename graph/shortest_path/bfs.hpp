#include"../../../kyopro_library/template.hpp"

/// @brief 重みなしグラフ g の頂点 start からの最短距離を求める
/// @note O(E+V)
VL BFS(const VVI& g, int start=0) {
    int n=g.size();
    VL ret(n,INF); ret[start]=0;
    queue<int> que; que.push(start);

    while(!que.empty()) {
        int now=que.front();que.pop();
        for(int nxt:g[now]) if(chmin(ret[nxt],ret[now]+1)) que.push(nxt);
    }

    return ret;
}