#pragma once
#include "../../../kyopro_library/template.hpp"

/// @brief 最大流
struct MaxFlow {
    /// @brief 辺構造体
    struct Edge {
        int from; ///< 始点
        int to; ///< 終点
        int rev; ///< 逆辺のインデックス
        ll cap; ///< 容量
        ll flow; ///< 流量
        bool isrev;
        Edge(int from, int to, ll cap, int rev, bool isrev):from(from),to(to),rev(rev),cap(cap),flow(0),isrev(isrev) {}
    };

    MaxFlow(int n):graph(n),level(n),iter(n) {}

    /// @brief 容量 cap の辺を追加する
    void add_edge(int from, int to, ll cap) {
        graph[from].push_back(Edge(from,to,cap,graph[to].size(),false));
        graph[to].push_back(Edge(to,from,0,graph[from].size()-1,true));
    }

private:
    vector<vector<Edge>> graph;
    vector<int> level,iter;
    void bfs(int s) {
        fill(level.begin(),level.end(),-1);
        queue<int> que;
        level[s]=0;
        que.push(s);
        while(!que.empty()) {
            int v=que.front();
            que.pop();
            for(auto &e:graph[v]) {
                if(e.cap>0&&level[e.to]<0) {
                    level[e.to]=level[v]+1;
                    que.push(e.to);
                }
            }
        }
    }
    ll dfs(int v, int t, ll f) {
        if(v==t) return f;
        for(int& i=iter[v]; i<(int)graph[v].size(); i++) {
            auto& e=graph[v][i];
            if(e.cap>0&&level[v]<level[e.to]) {
                ll d=dfs(e.to,t,min(f,e.cap));
                if(d>0) {
                    e.cap-=d,graph[e.to][e.rev].cap+=d;
                    e.flow+=d,graph[e.to][e.rev].flow-=d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    /// @brief s から t への最大流を求める
    /// @note O(V^2 E)
    ll flow(int s, int t) {
        ll ret=0;
        while(true) {
            bfs(s);
            if(level[t]==-1) return ret;
            fill(iter.begin(),iter.end(),0);
            ll f;
            while((f=dfs(s,t,INFL))>0) ret+=f;
        }
    }

    /// @brief 直前に流したフローから最小カットを復元する
    /// @brief 始点 v から到達可能か否か
    vector<int> mincut(int v=0) {
        vector<int> ret(graph.size());
        queue<int> que;
        que.push(v);
        ret[v]=true;
        while(!que.empty()) {
            int v=que.front();
            que.pop();
            for(auto& e:graph[v]) {
                if(e.cap>0&&!ret[e.to]) {
                    ret[e.to]=true;
                    que.push(e.to);
                }
            }
        }
        return ret;
    }

    /// @brief 直前に流したフローの辺の情報を返す
    vector<Edge> get_edges() {
        vector<Edge> ret;
        for(int i=0; i<graph.size(); i++) for(auto &e:graph[i]) if(!e.isrev) ret.push_back(e);
        return ret;
    }
};