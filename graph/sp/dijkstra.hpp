#include"../../../kyopro_library/template.hpp"

/// @brief ダイクストラ法
/// @brief グラフ g に対し、頂点 start から各頂点までの最短距離を求める
/// @note O(E log V)
VL Dijkstra(const WG& g,int start=0){
	int n=g.size();
	VL ret(n,INFL);
	ret[start]=0;
	rpriority_queue<pair<ll,int>>pq;
	pq.push({0,start});

	while(!pq.empty()){
		auto[ret_sum,now]=pq.top();pq.pop();
		if(ret[now]<ret_sum) continue;

		for(auto[nxt,cost]:g[now])if(chmin(ret[nxt],ret[now]+cost)) pq.push({ret[nxt],nxt});
	}

	return ret;
}