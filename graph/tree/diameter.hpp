#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/shortest_path/dijkstra.hpp"
#include"../../../kyopro_library/graph/shortest_path/bfs.hpp"

///@brief 重み付き木 g の直径を求める
///@return 直径上の頂点の配列と端点間の距離のペア
pair<vector<int>,ll> TreeDiameter(const vector<vector<pair<int,ll>>>& g) {
    vector<ll> dist=Dijkstra(g);
    int s=max_element(all(dist))-dist.begin();
    dist=Dijkstra(g,s);
    int t=max_element(all(dist))-dist.begin();
    vector<int> path;
    int now=t;
    while(now!=s) {
        path.push_back(now);
        for(auto[nxt,cost]:g[now]) {
            if(dist[now]==dist[nxt]+cost) {
                now=nxt;
                break;
            }
        }
    }
    path.push_back(s);
    ll diameter=dist[t];
    return {path,diameter};
}

///@brief 木 g の直径を求める
///@return 直径上の頂点の配列と端点間の距離のペア
pair<vector<int>,int> TreeDiameter(const vector<vector<int>>& g) {
    vector<ll> dist=BFS(g);
    int s=max_element(all(dist))-dist.begin();
    dist=BFS(g,s);
    int t=max_element(all(dist))-dist.begin();
    vector<int> path;
    int now=t;
    while(now!=s) {
        path.push_back(now);
        for(int nxt:g[now]) {
            if(dist[now]==dist[nxt]+1) {
                now=nxt;
                break;
            }
        }
    }
    path.push_back(s);
    int diameter=dist[t];
    return {path,diameter};
}