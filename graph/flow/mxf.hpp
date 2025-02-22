#include "../../../kyopro_library/template.hpp"

// 最大流 Dinic
struct MXF{
	struct Edge{
		int to,rev;
		ll cap;
		Edge(int to,ll cap,int rev):to(to),cap(cap),rev(rev){}
	};

	vector<vector<Edge>> graph;
	vector<int> level,iter;

	MXF(int n):graph(n),level(n),iter(n){}

	// add_edge(s, t, cap) : s -> t に容量 cap の辺を追加する
	// 償却 O(1)
	void add_edge(int from,int to,ll cap){
		graph[from].emplace_back(to,cap,graph[to].size());
		graph[to].emplace_back(from,0,(int)graph[from].size()-1);
	}

	void bfs(int s){
		fill(level.begin(),level.end(),-1);
		queue<int> q;
		level[s]=0;
		q.push(s);
		while(!q.empty()){
			int v=q.front();
			q.pop();
			for(auto &e:graph[v]){
				if(e.cap>0&&level[e.to]<0){
					level[e.to]=level[v]+1;
					q.push(e.to);
				}
			}
		}
	}

	ll dfs(int v,int t,ll f){
		if(v==t) return f;
		for(int &i=iter[v];i<(int)graph[v].size();i++){
			auto &e=graph[v][i];
			if(e.cap>0&&level[v]<level[e.to]){
				ll d=dfs(e.to,t,min(f,e.cap));
				if(d>0){
					e.cap-=d;
					graph[e.to][e.rev].cap+=d;
					return d;
				}
			}
		}
		return 0;
	}

	// flow(s, t) : s から t への最大流を求める
	// O(V^2 E)
	ll flow(int s,int t){
		ll ret=0;
		while(true){
			bfs(s);
			if(level[t]<0) return ret;
			fill(iter.begin(),iter.end(),0);
			ll f;
			while((f=dfs(s,t,INFL))>0) ret+=f;
		}
	}

	// mincut(v) : 直前に流したフローから最小カットを復元する
	vector<bool> mincut(int v=0){
		vector<bool> ret(graph.size());
		queue<int> q;
		q.push(v);
		ret[v]=true;
		while(!q.empty()){
			int v=q.front();
			q.pop();
			for(auto &e:graph[v]){
				if(e.cap>0&&!ret[e.to]){
					ret[e.to]=true;
					q.push(e.to);
				}
			}
		}
		return ret;
	}
};