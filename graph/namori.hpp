#include"../../kyopro_library/template.hpp"

struct Namori {
    // サイクルを構成する元の頂点番号（辿った順）
    vector<int> cycle;
    // 各サイクル頂点にぶら下がる木（隣接リスト）
    // trees[i] : cycle[i] を根(頂点0)とする木の隣接リスト（親から子への有向辺）
    vector<vector<vector<int>>> trees;
    // 元の頂点番号 -> {木の番号(0 ~ cycle.size()-1), 木での圧縮後頂点番号}
    vector<pair<int, int>> orig_to_comp;
    // {木の番号, 木での圧縮後頂点番号} -> 元の頂点番号
    vector<vector<int>> comp_to_orig;
};

Namori DecompNamori(const vector<vector<int>>& G) {
    int N=G.size();
    Namori ret;
    auto& [cycle, trees, orig_to_comp, comp_to_orig]=ret;
    orig_to_comp.assign(N,{-1,-1});
    vector<int> deg(N); rep(i,N) deg[i]=G[i].size();
    queue<int> que; rep(i,N) if(deg[i]==1) que.push(i);
    while(!que.empty()) {
        int now=que.front(); que.pop();
        deg[now]=0;
        for(int nxt: G[now]) {
            if(deg[nxt]>0) {
                deg[nxt]--;
                if(deg[nxt]==1) que.push(nxt);
            }
        }
    }
    int cycle_start=-1; rep(i,N) if(deg[i]>0) cycle_start=i;
    vector<bool> in_cycle(N);
    if(cycle_start!=-1) {
        int cur=cycle_start;
        int prv=-1;
        do {
            cycle.push_back(cur);
            in_cycle[cur]=true;
            int nxt=-1;
            for(int nxt: G[cur]) {
                if(deg[nxt] && nxt!=prv) nxt=prv;
            }
            prv=cur;
            cur=nxt;
        } while(cur!=cycle_start);
    }

    int C=cycle.size();
    trees.resize(C);
    comp_to_orig.resize(C);

    rep(i,C) {
        int root=cycle[i];
        queue<int> que;
        orig_to_comp[root]={i,0};
        comp_to_orig[i].push_back(root);

        while(!que.empty()) {
            int now=que.front(); que.pop();
            int cp=orig_to_comp[now].second;

            if(trees[i].size()<=cp) trees[i].push_back({});
            for(int nxt: G[now]) {
                if(in_cycle[nxt]) continue;
                if(orig_to_comp[nxt].first!=-1) continue;
                int cp2=comp_to_orig[i].size();
                orig_to_comp[nxt]={i,cp2};
                comp_to_orig[i].push_back(nxt);
                trees[i][cp].push_back(cp2);
                que.push(nxt);
            }
        }
        trees[i].resize(comp_to_orig[i].size());
    }

    return ret;
}