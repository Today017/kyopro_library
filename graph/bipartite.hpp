#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/flow/max_flow.hpp"
#include"../../kyopro_library/graph/bicolor.hpp"

///@brief 二部グラフのパラメータ
struct BiInfo {
    vector<pair<int,int>> max_matching; ///< 最大マッチング
    vector<pair<int,int>> min_edge_cover; ///< 最小辺被覆
    vector<int> max_independent_set; ///< 最大独立集合
    vector<int> min_vertex_cover; ///< 最小頂点被覆
};

///@brief 二部グラフのパラメータを求める
///@note O(E*sqrt(V))
///@attention G は二部グラフであること
BiInfo GetBiInfo(const vector<vector<int>>& G) {
    int N=G.size();

    BiInfo ret;
    auto& [
        max_matching,
        min_edge_cover,
        max_independent_set,
        min_vertex_cover
    ]=ret;
    auto col=BiColorize(G);
    int s=N, t=N+1;
    MaxFlow mxf(N+2);

    rep(i,N) {
        if(!col[i]) {
            for(int j: G[i]) mxf.add_edge(i,j,1);
            mxf.add_edge(s,i,1);
        } else {
            mxf.add_edge(i,t,1);
        }
    }

    mxf.flow(s,t);

    auto edges=mxf.get_edges();
    for(auto& e: edges) {
        if(e.from==s) continue;
        if(e.to==t) continue;
        if(e.flow==1) max_matching.push_back({e.from,e.to});
    }

    //最小辺被覆を最大マッチングから構成する
    //手順: まずマッチング辺ですべての被覆済み頂点をマークし、それでも被覆されていない（かつ孤立でない）頂点に対して任意の隣接辺を1つ追加する
    {
        vector<bool> covered(N,false);
        for(auto &e: max_matching) {
            covered[e.first]=true;
            covered[e.second]=true;
            min_edge_cover.push_back(e);
        }
        rep(i,N) {
            if(!covered[i] && !G[i].empty()) {
                int j=G[i][0];
                min_edge_cover.push_back({i,j});
                covered[i]=true;
                covered[j]=true;
            }
        }
    }

    //mincut := 頂点sから到達可能か
    auto mincut=mxf.mincut(s);
    rep(i,N) {
        if(col[i]) {
            if(mincut[i]) min_vertex_cover.push_back(i);
            else max_independent_set.push_back(i);
        } else {
            if(mincut[i]) max_independent_set.push_back(i);
            else min_vertex_cover.push_back(i);
        }
    }

    return ret;
}
