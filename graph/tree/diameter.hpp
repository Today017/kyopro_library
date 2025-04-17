#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/sp/dijkstra.hpp"
#include"../../../kyopro_library/graph/sp/bfs.hpp"

pair<VI,ll>TreeDiameter(const vector<vector<pair<int,ll>>>&g){
	VL dist=Dijkstra(g);
	int s=max_element(ALL(dist))-dist.begin();
	dist=Dijkstra(g,s);
	int t=max_element(ALL(dist))-dist.begin();
	VI path;
	int now=t;
	while(now!=s){
		path.push_back(now);
		for(auto[nxt,cost]:g[now]){
			if(dist[now]==dist[nxt]+cost){
				now=nxt;
				break;
			}
		}
	}
	path.push_back(s);
	ll diameter=dist[t];
	return{path,diameter};
}

pair<VI,ll>TreeDiameter(const vector<VI>&g){
	VL dist=BFS(g);
	int s=max_element(ALL(dist))-dist.begin();
	dist=BFS(g,s);
	int t=max_element(ALL(dist))-dist.begin();
	VI path;
	int now=t;
	while(now!=s){
		path.push_back(now);
		for(int nxt:g[now]){
			if(dist[now]==dist[nxt]+1){
				now=nxt;
				break;
			}
		}
	}
	path.push_back(s);
	ll diameter=dist[t];
	return{path,diameter};
}