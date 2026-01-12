#pragma once
#include "../../../kyopro_library/template.hpp"

///@brief 最小費用流
///@note コスト負の辺を許容する。負の閉路はダメ。
struct MinCostFlow {
    ///@brief 辺構造体
    struct Edge {
        int from; ///< 始点
        int to; ///< 終点
        int rev; ///< 逆辺のインデックス
        ll cap; ///< 容量
        ll cost; ///< コスト
        bool isrev;
        Edge(int from, int to, ll cap, ll cost, int rev, bool isrev): from(from), to(to), cap(cap), cost(cost), rev(rev), isrev(isrev) {}
    };

    MinCostFlow(int n) { graph.resize(n); dist.resize(n); pot.resize(n); pv.resize(n); pe.resize(n); }

    ///@brief s -> t に容量 cap, コスト cost の辺を追加する
    ///@note cost は負でも良い
    void add_edge(int from, int to, ll cap, ll cost) {
        graph[from].push_back(Edge(from,to,cap,cost,graph[to].size(),false));
        graph[to].push_back(Edge(to,from,0,-cost,(int)graph[from].size()-1,true));
    }

    ///@brief 全ての辺を返す
    ///@note O(V+E)
    ///@note 直前に流した flow による残余であることに注意
    vector<Edge> get_edges() {
        vector<Edge> ret;
        rep(i,graph.size()) for(auto &e:graph[i]) if(!e.isrev) ret.push_back(e);
        return ret;
    }

    ///@brief s から t へ流量 f の最小費用流のコストを求める
    ///@brief 流せない場合は INFL を返す
    ///@note O(FE log V)
    ll flow(int s, int t, ll f) {
        int n=graph.size();
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
        fill(all(pot),0); fill(all(pv),0); fill(all(pe),0);
        ll ret=0;

        while(f>0) {
            fill(all(dist),INFL);
            dist[s]=0;
            pq.push({0,s});
            while(!pq.empty()) {
                auto [tmp,now]=pq.top();
                pq.pop();
                if(dist[now]<tmp) continue;
                rep(i,graph[now].size()) {
                    auto [from,to,rev,cap,cost,isrev]=graph[now][i];
                    ll ncost=dist[now]+cost+pot[now]-pot[to];
                    if(cap>0 && dist[to]>ncost) {
                        dist[to]=ncost; pv[to]=now; pe[to]=i;
                        pq.push({dist[to],to});
                    }
                }
            }
            if(dist[t]==INFL) return INFL;
            rep(i,n) pot[i]+=dist[i];
            ll d=f;
            for(int v=t; v!=s; v=pv[v]) chmin(d,graph[pv[v]][pe[v]].cap);
            f-=d; ret+=d*pot[t];
            for(int v=t; v!=s; v=pv[v]) {
                auto& e=graph[pv[v]][pe[v]];
                e.cap-=d; graph[v][e.rev].cap+=d;
            }
        }

        return ret;
    }

private:
    vector<vector<Edge>> graph;
    vector<ll> dist,pot; // 距離, ポテンシャル
    vector<int> pv,pe;
};