#pragma once
#include"../../kyopro_library/template.hpp"

template<typename T=ll>
struct Graph {
    struct Edge {
        ii to, from, idx;
        T w;
    };
    ii idxall=0;

    vector<vector<Edge>> adj;
    Graph(ii n): adj(n), indeg(n) {}
    vi indeg;

    bool weighted=false, di=false, onebased=true;
    void read(ii m) {
        rep(i,m) {
            ii a,b; cin>>a>>b;
            if(onebased) a--, b--;
            T w=1;
            if(weighted) cin>>w;
            if(di) add_edge(a,b,w);
            else add_undedge(a,b,w);
        }
    }

    void add_edge(ii u, ii v, T w=1) {
        adj[u].push_back({v, u, idxall++, w});
        indeg[v]++;
    }

    void add_undedge(ii u, ii v, T w=1) {
        add_edge(u,v,w);
        add_edge(v,u,w);
    }

    const vector<Edge>& next(ii u) const { return adj[u]; }
    vector<Edge>& next(ii u) { return adj[u]; }

    ii size() const { return adj.size(); }
};

#define adj(nxt,w,G) for(auto [nxt,_,idx,w]: G.next(now))
