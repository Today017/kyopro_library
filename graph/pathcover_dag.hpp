#include "../../kyopro_library/graph/flow/max_flow.hpp"

///@brief DAGの最小パス被覆のサイズを求める
///@brief Dilworthの定理より、最大独立集合のサイズと等しくなる
///@note O(E sqrt(V))
int PathCoverDag(const vector<vector<int>>& g) {
    int N=g.size();
    MaxFlow mf(N*2+2);
    int source=N*2, sink=source+1;
    rep(i,N) for(int j: g[i]) mf.add_edge(i,j+N,1);
    rep(i,N) {
        mf.add_edge(source,i,1);
        mf.add_edge(i+N,sink,1);
    }
    return N-mf.flow(source,sink);
}
