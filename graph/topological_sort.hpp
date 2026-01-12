#include"../../kyopro_library/template.hpp"

///@brief グラフ g をトポロジカルソートする
///@note グラフにサイクルがある場合は空の配列を返す
///@note O(V+E)
vector<int> TopologicalSort(const vector<vector<int>>& g) {
    int n=g.size();
    vector<int> indeg(n);
    rep(i,n) for(int nxt:g[i]) indeg[nxt]++;
    queue<int> que;
    rep(i,n) if(indeg[i]==0) que.push(i);
    vector<int> ret;

    while(!que.empty()) {
        int now=que.front(); que.pop();
        for(int nxt: g[now]) {
            indeg[nxt]--;
            if(indeg[nxt]==0) que.push(nxt);
        }
        ret.push_back(now);
    }

    if(ret.size()!=n) return {};
    return ret;
}