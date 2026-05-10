#pragma once
#include"../../../kyopro_library/template.hpp"

/// @brief BFS 重みなしグラフに対する最短経路
vector<ll> BFS(const vector<vector<int>>& G, int start=0) {
    int N=G.size();
    vector<ll> ret(N,INF); ret[start]=0;
    queue<int> que; que.push(start);

    while(!que.empty()) {
        int now=que.front(); que.pop();
        for(int nxt: G[now]) if(chmin(ret[nxt],ret[now]+1)) que.push(nxt);
    }

    return ret;
}