#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 強連結成分分解の情報
struct SccInfo{
    VVI members; ///< 各強連結成分の頂点
    VVI graph_decomposed; ///< 強連結成分による分解グラフ
    VI group; ///< 各頂点の所属する強連結成分の番号
};

/// @brief グラフ g の強連結成分分解を行う
/// @brief { 各強連結成分の頂点, 強連結成分による分解グラフ, 各頂点の所属する強連結成分の番号 } を返す
/// @note O(V+E)
SccInfo SccDecomposition(const VVI& g){
    int n=g.size();
    VVI g2(n);
    REP(i,n)for(int j:g[i]) g2[j].push_back(i);
    VI order,component(n,-1),seen(n,false);

    auto f=[&](auto f, int now)-> void {
        seen[now]=true;
        for(int nxt:g[now])if(!seen[nxt]) f(f,nxt);
        order.push_back(now);
    };

    auto f2=[&](auto f2, int now, int idx)-> void {
        component[now]=idx;
        for(int nxt:g2[now])if(component[nxt]==-1) f2(f2,nxt,idx);
    };

    REP(i,n)if(!seen[i]) f(f,i);

    reverse(ALL(order));
    int idx=0;
    for(int now:order)if(component[now]==-1) f2(f2,now,idx),idx++;

    int n_n=*max_element(ALL(component))+1;
    VVI ret(n_n),ret2(n_n);
    REP(i,n) ret[component[i]].push_back(i);
    REP(i,n)for(int j:g[i])if(component[i]!=component[j]) ret2[component[i]].push_back(component[j]);
    REP(i,n_n) UQ(ret2[i]);

    return {ret,ret2,component};
}