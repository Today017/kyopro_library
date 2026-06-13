#pragma once
#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/graph.hpp"

/// @brief BFS 重みなしグラフに対する最短経路
template<typename T>
vector<T> BFS(const Graph<T>& G, int start=0) {
    int N=G.size();
    vector<T> ret(N,inf<T>); ret[start]=0;
    queue<int> que; que.push(start);

    while(!que.empty()) {
        int now=que.front(); que.pop();
        for(auto e: G.next(now)) if(chmin(ret[e.to],ret[now]+1)) que.push(e.to);
    }

    return ret;
}
