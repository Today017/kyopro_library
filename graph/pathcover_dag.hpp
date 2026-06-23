#pragma once
#include "../../kyopro_library/graph/flow/max_flow.hpp"
#include "../../kyopro_library/graph/graph.hpp"

/// @brief DAGの最小パス被覆のサイズを求める
/// @brief Dilworthの定理より、最大独立集合のサイズと等しくなる
/// @note O(E sqrt(V))
template <typename T>
ii PathCoverDag(const Graph<T>& G) {
    ii N = G.size();
    MaxFlow mf(N * 2 + 2);
    ii source = N * 2, sink = source + 1;
    rep(i, N) for(auto e : G.next(i)) mf.add_edge(i, e.to + N, 1);
    rep(i, N) {
        mf.add_edge(source, i, 1);
        mf.add_edge(i + N, sink, 1);
    }
    return N - mf.flow(source, sink);
}
