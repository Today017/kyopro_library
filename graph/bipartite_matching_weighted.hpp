#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/flow/min_cost_flow.hpp"

/// @brief 重み付き最大二部マッチング（重み最大化）
template<bool MAX>
struct BipartiteMatchingWeighted {
    MinCostFlow mcf;
    int start, goal;
    BipartiteMatchingWeighted(int n): mcf(n+2), start(n), goal(n+1) {}
    VI left,right;

    /// @brief 左側の頂点 u と右側の頂点 v に重み w の辺を追加する
    void add_edge(int u, int v, ll w) {
        left.push_back(u);
        right.push_back(v);
        if(MAX) w=-w;
        mcf.add_edge(u,v,1,w);
    }

    /// @brief 頂点 u を左側に追加する
    void add_left(int u) { left.push_back(u); }

    /// @brief 頂点 v を右側に追加する
    void add_right(int v) { right.push_back(v); }

    /// @brief 重み付き最大二部マッチング問題を解く
    /// @brief `ret[i] := i 組のマッチングが成立しているときの重み`
    VL solve() {
        UQ(left); UQ(right);
        for(int u: left) mcf.add_edge(start,u,1,0);
        for(int v: right) mcf.add_edge(v,goal,1,0);

        VL ret;
        ret.push_back(0);
        while(true) {
            ll res=mcf.flow(start,goal,1);
            if(res==INFL) break;
            if(MAX) res=-res;
            ret.push_back(ret.back()+res);
        }
        return ret;
    }
};