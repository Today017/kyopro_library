#include "../../../kyopro_library/template.hpp"

// 最小費用流
// コスト負の辺を許容する。負の閉路はダメ。
struct MCF{
	struct Edge{
		int from,to,rev;
		ll cap,cost;
		bool isrev;
		Edge(int from,int to,ll cap,ll cost,int rev,bool isrev):from(from),to(to),cap(cap),cost(cost),rev(rev),isrev(isrev){}
	};

	vector<vector<Edge>> graph;
	vector<ll> dist,pot; // 距離, ポテンシャル
	vector<int> pv,pe;

	MCF(int n){graph.resize(n),dist.resize(n),pot.resize(n),pv.resize(n),pe.resize(n);}

	// add_edge(s, t, cap, cost) : s -> t に容量 cap, コスト cost の辺を追加する
	// cost は負でも良い。
	// 償却 O(1)
	void add_edge(int from,int to,ll cap,ll cost){
		graph[from].push_back(Edge(from,to,cap,cost,graph[to].size(),false));
		graph[to].push_back(Edge(to,from,0,-cost,(int)graph[from].size()-1,true));
	}

	// get_edges() : 全ての辺を返す
	// O(V+E)
	// 直前に流した flow による残余であることに注意
	vector<Edge> get_edges(){
		vector<Edge> ret;
		for(int i=0;i<(int)graph.size();i++)for(auto &e:graph[i]) if(!e.isrev) ret.push_back(e);
		return ret;
	}

	// flow(s, t, f) : s から t へ流量 f の最小費用流のコストを求める
	// 流せない場合は INFL を返す
	// O(FE log V)
	ll flow(int s,int t,ll f){
		int n=graph.size();
		priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
		fill(pot.begin(),pot.end(),0),fill(pv.begin(),pv.end(),0),fill(pe.begin(),pe.end(),0);
		ll ret=0;

		while(f>0){
			fill(dist.begin(),dist.end(),INFL);
			dist[s]=0;
			pq.push({0,s});
			while(!pq.empty()){
				auto [tmp,now]=pq.top();
				pq.pop();
				if(dist[now]<tmp) continue;
				for(int i=0;i<(int)graph[now].size();i++){
					auto[from,to,rev,cap,cost,isrev]=graph[now][i];
					ll ncost=dist[now]+cost+pot[now]-pot[to];
					if(cap>0&&dist[to]>ncost){
						dist[to]=ncost,pv[to]=now,pe[to]=i;
						pq.push({dist[to],to});
					}
				}
			}
			if(dist[t]==INFL) return INFL;
			for(int i=0;i<n;i++) pot[i]+=dist[i];
			ll d=f;
			for(int v=t;v!=s;v=pv[v]) d=min(d,graph[pv[v]][pe[v]].cap);
			f-=d,ret+=d*pot[t];
			for(int v=t;v!=s;v=pv[v]){
				auto &e=graph[pv[v]][pe[v]];
				e.cap-=d,graph[v][e.rev].cap+=d;
			}
		}

		return ret;
	}
};