#include"../../kyopro_library/template.hpp"

/// @brief グラフ g をトポロジカルソートする
/// @note グラフにサイクルがある場合は空の配列を返す
/// @note O(V+E)
VI TopologicalSort(const VVI& g){
    int n=g.size();
    VI indeg(n);
    REP(i,n)for(int nxt:g[i]) indeg[nxt]++;
    queue<int> que;
    REP(i,n)if(indeg[i]==0) que.push(i);
    VI ret;

    while(!que.empty()){
        int now=que.front();
        que.pop();
        for(int nxt:g[now]){
            indeg[nxt]--;
            if(indeg[nxt]==0) que.push(nxt);
        }
        ret.push_back(now);
    }

    if(ret.size()!=n) return {};
    return ret;
}