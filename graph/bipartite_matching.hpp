#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/flow/max_flow.hpp"

/// @brief 二部グラフの最大マッチングを返す
/// @note O(E*sqrt(V))
/// @attention G は二部グラフであること
vector<pair<int,int>> BipartiteMatching(const VVI& g) {
    int n=g.size();
    MaxFlow mxf(n+2);
    int s=n,t=n+1;
    REP(i,n) {
        for(int j:g[i]) mxf.add_edge(i,j,1);
        mxf.add_edge(s,i,1);
        mxf.add_edge(i,t,1);
    }

    mxf.flow(s,t);

    vector<pair<int,int>> ret;
    auto edges=mxf.get_edges();
    for(auto& e:edges) {
        if(e.from==s) continue;
        if(e.to==t) continue;
        if(e.flow==1) ret.push_back({e.from,e.to});
    }

    return ret;
}

/// @brief 二部グラフのパラメータ
struct BiInfo {
    int max_matching; ///< 最大マッチング
    int min_edge_cover; ///< 最小辺被覆
    int max_independent_set; ///< 最大独立集合
    int min_vertex_cover; ///< 最小頂点被覆
    /// @note min_edge_cover=-1 のときは孤立点がある
};

/// @brief 二部グラフのパラメータを求める
/// @note O(E*sqrt(V))
/// @attention G は二部グラフであること
BiInfo GetBiInfo(const VVI& g) {
    int n=g.size();
    int isolation=0;
    REP(i,n) if(g[i].size()==0) isolation++;

    BiInfo ret;
    int m=BipartiteMatching(g).size();
    ret.max_matching=m;
    ret.min_edge_cover=isolation==0?n-m:-1;
    ret.min_vertex_cover=m;
    ret.max_independent_set=n-m;

    return ret;
}
