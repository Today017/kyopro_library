#pragma once
#include "../../../kyopro_library/template.hpp"

/// @brief 最大流
struct MaxFlow {
    /// @brief 辺構造体
    struct Edge {
        ii from;  ///< 始点
        ii to;  ///< 終点
        ii rev;  ///< 逆辺のインデックス
        ll cap;  ///< 容量
        ll flow;  ///< 流量
        bool isrev;
        Edge(ii from, ii to, ll cap, ii rev, bool isrev) : from(from), to(to), rev(rev), cap(cap), flow(0), isrev(isrev) {}
    };

    MaxFlow(ii n) : graph(n), level(n), iter(n) {}
    MaxFlow() = default;

    /// @brief 容量 cap の辺を追加する
    void add_edge(ii from, ii to, ll cap) {
        graph[from].push_back(Edge(from, to, cap, graph[to].size(), false));
        graph[to].push_back(Edge(to, from, 0, graph[from].size() - 1, true));
    }

private:
    vector<vector<Edge>> graph;
    vi level, iter;

    void bfs(ii s) {
        fill(all(level), -1);
        level[s] = 0;
        queue<ii> que;
        que.push(s);
        while(!que.empty()) {
            ii v = que.front();
            que.pop();
            for(auto& e : graph[v]) {
                if(e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    ll dfs(ii v, ii t, ll f) {
        if(v == t) return f;
        for(ii& i = iter[v]; i < (ii)graph[v].size(); i++) {
            auto& e = graph[v][i];
            if(e.cap > 0 && level[v] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.cap));
                if(d > 0) {
                    e.cap -= d, graph[e.to][e.rev].cap += d;
                    e.flow += d, graph[e.to][e.rev].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    /// @brief s から t への最大流を求める
    /// @note O(V^2 E)
    ll flow(ii s, ii t) {
        ll ret = 0;
        while(true) {
            bfs(s);
            if(level[t] == -1) return ret;
            fill(all(iter), 0);
            ll f;
            while((f = dfs(s, t, INFL)) > 0) ret += f;
        }
    }

    /// @brief 直前に流したフローから最小カットを復元する
    /// @brief 始点 v から到達可能か否か
    vi mincut(ii v = 0) {
        vi ret(graph.size());
        ret[v] = true;
        queue<ii> que;
        que.push(v);
        while(!que.empty()) {
            ii v = que.front();
            que.pop();
            for(auto& e : graph[v]) {
                if(e.cap > 0 && !ret[e.to] /*&& !e.isrev*/) {
                    ret[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return ret;
    }

    /// @brief 直前に流したフローの辺の情報を返す
    vector<Edge> get_edges() {
        vector<Edge> ret;
        rep(i, graph.size()) for(auto& e : graph[i]) if(!e.isrev) ret.push_back(e);
        return ret;
    }
};
