#pragma once
#include"../../kyopro_library/template.hpp"

///@brief 強連結成分分解の情報
struct SccInfo {
    vector<vector<int>> members; ///< 各強連結成分の頂点
    vector<vector<int>> graph_decomposed; ///< 強連結成分による分解グラフ
    vector<int> group; ///< 各頂点の所属する強連結成分の番号
};

///@brief グラフ G の強連結成分分解を行う
///@brief { 各強連結成分の頂点, 強連結成分による分解グラフ, 各頂点の所属する強連結成分の番号 } を返す
///@note O(V+E)
SccInfo SccDecomposition(const vector<vector<int>>& G) {
    int N=G.size();
    vector<vector<int>> g2(N);
    rep(i,N) for(int j: G[i]) g2[j].push_back(i);
    vector<int> order, comp(N,-1), seen(N,false);

    auto dfs=[&](auto dfs, int now)-> void {
        seen[now]=true;
        for(int nxt: G[now]) if(!seen[nxt]) dfs(dfs,nxt);
        order.push_back(now);
    };
    auto dfs2=[&](auto dfs2, int now, int idx)-> void {
        comp[now]=idx;
        for(int nxt: g2[now]) if(comp[nxt]==-1) dfs2(dfs2,nxt,idx);
    };

    rep(i,N) if(!seen[i]) dfs(dfs,i);

    reverse(all(order));
    int idx=0;
    for(int now: order) if(comp[now]==-1) dfs2(dfs2,now,idx), idx++;

    int nN=*max_element(all(comp))+1;
    vector<vector<int>> ret(nN), ret2(nN);
    rep(i,N) ret[comp[i]].push_back(i);
    rep(i,N) for(int j: G[i]) if(comp[i]!=comp[j]) ret2[comp[i]].push_back(comp[j]);
    rep(i,nN) sort(all(ret2[i])), ret2[i].erase(unique(all(ret2[i])),ret2[i].end());

    return {ret,ret2,comp};
}