#pragma once
#include"../../../kyopro_library/template.hpp"

///@brief ダイクストラ法
///@brief 重み付きグラフ g に対し、頂点 start から各頂点までの最短距離を求める
///@note O(E log V)
vector<ll> Dijkstra(const vector<vector<pair<int,ll>>>& g, int start=0) {
    int n=g.size();
    vector<ll> ret(n,INFL); ret[start]=0;
    priority_queue<pair<ll,int>> pq; pq.push({0,start});

    while(!pq.empty()) {
        auto [tmp,now]=pq.top(); pq.pop(); tmp=-tmp;
        if(ret[now]<tmp) continue;
        for(auto [nxt,cost]: g[now]) if(chmin(ret[nxt],ret[now]+cost)) pq.push({-ret[nxt],nxt});
    }

    return ret;
}