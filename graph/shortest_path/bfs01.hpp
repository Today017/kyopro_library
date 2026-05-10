#pragma once
#include"../../../kyopro_library/template.hpp"

///@brief 01BFS
vector<int> BFS01(const vector<vector<pair<int,ll>>>& G, int start=0) {
    int N=G.size();
    vector<int> ret(N,INF); ret[start]=0;
    deque<pair<int,int>> dq; dq.push_front({0,start});

    while(!dq.empty()) {
        auto [tmp,now]=dq.front(); dq.pop_front();
        if(ret[now]<tmp) continue;
        for(auto [nxt,cost]: G[now]) {
            if(chmin(ret[nxt],ret[now]+cost)) {
                if(cost==0) dq.push_front({ret[nxt],nxt});
                else dq.push_back({ret[nxt],nxt});
            }
        }
    }

    return ret;
}
