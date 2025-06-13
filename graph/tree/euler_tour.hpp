#include"../../../kyopro_library/template.hpp"

/// @brief 木 g をオイラーツアーする
/// @brief `(行きがけ順, 深さ, 入力時刻, 出力時刻)` を返す
/// @details 部分木のクエリを列のに対する区間クエリとして扱えるようになる
/// @details 例えば、頂点 v の部分木はオイラーツアー後の列の区間 `[in[v], out[v])` に対応する
tuple<vector<int>,vector<int>,vector<int>,vector<int>> EulerTour(const vector<vector<int>>& g) {
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
    dfs(dfs,0,-1,0);

    return {tour,depth,in,out};
}