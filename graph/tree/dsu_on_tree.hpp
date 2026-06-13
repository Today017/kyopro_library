#pragma once
#include"../../../kyopro_library/template.hpp"

///@brief DSU on Tree
///@ref https://atcoder.jp/contests/abc454/editorial/19112
struct DsuOnTree {
    DsuOnTree(const vector<vi>& g, int root):
        n(g.size()), G(g), heavy(n,-1), root(root) {
        build();
    }

    void run(auto&& Add, auto&& Query, auto&& Reset) {
        auto efs=[&](auto&& efs, int now, int pre)-> void {
            for(int nxt: G[now]) if(nxt!=pre) efs(efs,nxt,now);
            Add(now);
        };

        auto dfs=[&](auto&& dfs, int now, int pre)-> void {
            for(int nxt: G[now]) if(nxt!=pre && nxt!=heavy[now]) {
                dfs(dfs,nxt,now);
                Reset();
            }

            if(heavy[now]!=-1) dfs(dfs,heavy[now],now);

            for(int nxt: G[now]) if(nxt!=pre && nxt!=heavy[now]) efs(efs,nxt,now);

            Add(now);
            Query(now);
        };

        dfs(dfs,root,-1);
    }

private:
    int n, root;
    vector<vi> G;
    vi heavy;

    void build() {
        vi ch(n);
        auto dfs=[&](auto&& dfs, int now, int pre)-> void {
            for(int nxt: G[now]) if(nxt!=pre) {
                dfs(dfs,nxt,now);
                if(heavy[now]==-1 || ch[heavy[now]]<ch[nxt]) heavy[now]=nxt;
                ch[now]+=ch[nxt];
            }
            ch[now]++;
        };
        dfs(dfs,root,-1);
    }
};
