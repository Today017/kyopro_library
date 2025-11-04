#include"../../../kyopro_library/template.hpp"

struct EulerTourInfo {
    vector<int> tour; ///< 行きがけ順の頂点列 tour[i] := i番目に訪問した頂点
    vector<int> depth; ///< 各頂点の深さ depth[v] := 頂点 v の深さ
    vector<int> in; ///< 各頂点の入力時刻 in[v] := 頂点 v を訪問した時刻
    vector<int> out; ///< 各頂点の出力時刻 out[v] := 頂点 v の部分木の探索が終了した時刻
};

/// @brief 木 g をオイラーツアーする
/// @brief `(行きがけ順, 深さ, 入力時刻, 出力時刻)` を返す
/// @details 部分木のクエリを列のに対する区間クエリとして扱えるようになる
/// @details 例えば、頂点 v の部分木はオイラーツアー後の列の区間 `[in[v], out[v])` に対応する
EulerTourInfo EulerTour(const vector<vector<int>>& g, int r=0) {
    int n=g.size();
    vector<int> tour,depth(n),in(n),out(n);
    int time=0;
    auto dfs=[&](auto&& dfs, int now, int pre, int d)-> void {
        depth[now]=d;
        in[now]=time++;
        tour.push_back(now);
        for(int nxt:g[now]) if(nxt!=pre) dfs(dfs,nxt,now,d+1);
        out[now]=time;
    };
    dfs(dfs,r,-1,0);

    return EulerTourInfo{tour,depth,in,out};
}
