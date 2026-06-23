#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/graph/graph.hpp"

/// @brief 二部グラフに対し、01の色分けをする
/// @brief 二部グラフでない場合は空の配列を返す
template <typename T>
vi BiColorize(const Graph<T>& G) {
    int N = G.size();
    vi col(N, -1);
    queue<int> que;
    rep(i, N) if(col[i] == -1) {
        col[i] = 0;
        que.push(i);
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            for(auto e : G.next(now)) {
                int c = col[now] ^ 1;
                if(col[e.to] == -1) {
                    col[e.to] = c;
                    que.push(e.to);
                } else if(col[e.to] != c) {
                    return {};
                }
            }
        }
    }
    return col;
}
