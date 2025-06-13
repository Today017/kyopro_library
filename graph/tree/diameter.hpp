#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/shortest_path/dijkstra.hpp"
#include"../../../kyopro_library/graph/shortest_path/bfs.hpp"

pair<vector<int>,ll> TreeDiameter(const vector<vector<pair<int,ll>>>& g) {
    vector<ll> dist=Dijkstra(g);
    int s=max_element(dist.begin(),dist.end())-dist.begin();
    dist=Dijkstra(g,s);
    int t=max_element(dist.begin(),dist.end())-dist.begin();
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

pair<vector<int>,ll>TreeDiameter(const vector<vector<int>>& g) {
    vector<ll> dist=BFS(g);
    int s=max_element(dist.begin(),dist.end())-dist.begin();
    dist=BFS(g,s);
    int t=max_element(dist.begin(),dist.end())-dist.begin();
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
    ll diameter=dist[t];
    return {path,diameter};
}