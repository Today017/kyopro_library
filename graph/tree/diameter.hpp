#pragma once
#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/shortest_path/dijkstra.hpp"
#include"../../../kyopro_library/graph/shortest_path/bfs.hpp"

///@brief 木 g の直径を求める
///@return 直径上の頂点の配列と端点間の距離のペア
template<typename T>
pair<vi,int> TreeDiameter(const Graph<T>& G) {
    vector<ll> dist=BFS(G);
    int s=max_element(all(dist))-dist.begin();
    dist=BFS(G,s);
    int t=max_element(all(dist))-dist.begin();
    vi path;
    int now=t;
    while(now!=s) {
        path.push_back(now);
        for(auto e: G.next(now)) {
            if(dist[now]==dist[e.to]+1) {
                now=e.to;
                break;
            }
        }
    }
    path.push_back(s);
    int diameter=dist[t];
    return {path,diameter};
}

///@brief 重み付き木 g の直径を求める
///@return 直径上の頂点の配列と端点間の距離のペア
//pair<vi,ll> TreeDiameter(const vector<vector<pair<int,ll>>>& g) {
template<typename T>
pair<vi,T> TreeDiameterDij(const Graph<T>& G) {
    vector<ll> dist=Dijkstra(G);
    int s=max_element(all(dist))-dist.begin();
    dist=Dijkstra(G,s);
    int t=max_element(all(dist))-dist.begin();
    vi path;
    int now=t;
    while(now!=s) {
        path.push_back(now);
        for(auto e: G.next(now)) {
            if(dist[now]==dist[e.to]+e.w) {
                now=e.to;
                break;
            }
        }
    }
    path.push_back(s);
    T diameter=dist[t];
    return {path,diameter};
}
