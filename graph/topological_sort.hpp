#include"../../kyopro_library/template.hpp"

///@brief グラフ G をトポロジカルソートする
///@note グラフにサイクルがある場合は空の配列を返す
///@note O(V+E)
vector<int> TopologicalSort(const vector<vector<int>>& G) {
    int N=G.size();
    vector<int> indeg(N);
    rep(i,N) for(int nxt: G[i]) indeg[nxt]++;
    queue<int> que;
    rep(i,N) if(indeg[i]==0) que.push(i);
    vector<int> ret;

    while(!que.empty()) {
        int now=que.front(); que.pop();
        for(int nxt: G[now]) {
            indeg[nxt]--;
            if(indeg[nxt]==0) que.push(nxt);
        }
        ret.push_back(now);
    }

    if(ret.size()!=N) return {};
    return ret;
}