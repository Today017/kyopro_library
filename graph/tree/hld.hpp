#include "../../../kyopro_library/template.hpp"

struct HLD{
	HLD(int n){resize(n);}
	void add_edge(int a,int b){graph[a].push_back(b),graph[b].push_back(a);}
	void build(int root=0){dfs1(root),dfs2(root,root);}
	HLD(const vector<vector<int>>&g,int root=0){
		resize(g.size());
		this->graph=g;
		build(root);
	}

	const vector<tuple<bool,int,int>>&path(int u,int v){
		vector<tuple<bool,int,int>>ret;
		while(head[u]!=head[v]){
			if(dep[head[u]]>dep[head[v]]){
				ret.push_back({true,pos[head[u]],pos[u]});
				u=par[head[u]];
			}else{
				ret.push_back({false,pos[head[v]],pos[v]});
				v=par[head[v]];
			}
		}
		if(dep[u]>dep[v]){
			ret.push_back({true,pos[v],pos[u]});
		}else{
			ret.push_back({false,pos[u],pos[v]});
		}
		return ret;
	}
	int lca(int u,int v){
		while(head[u]!=head[v]){
			if(dep[head[u]]>dep[head[v]]){
				u=par[head[u]];
			}else{
				v=par[head[v]];
			}
		}
		return dep[u]<dep[v]?u:v;
	}
	int at(int v){return pos[v];}

private:
	vector<vector<int>>graph;
	vector<int>sz,par,dep,hld,pos,head;
	void resize(int n){graph.resize(n),sz.resize(n),par.resize(n),dep.resize(n),pos.resize(n),head.resize(n);}
	void dfs1(int now,int pre=-1){
		par[now]=pre;
		int res=1;
		for(int nxt:graph[now]){
			if(nxt==pre)continue;
			dep[nxt]=dep[now]+1;
			dfs1(nxt,now);
			res+=sz[nxt];
		}
		sz[now]=res;
	}
	void dfs2(int now,int a,int pre=-1){
		pos[now]=hld.size();
		hld.push_back(now);
		head[now]=a;
		if(sz[now]==1)return;
		int mx=0,idx=0;
		for(int nxt:graph[now]){
			if(nxt==pre)continue;
			if(mx<sz[nxt]){
				mx=sz[nxt];
				idx=nxt;
			}
		}
		dfs2(idx,a,now);
		for(int nxt:graph[now]){
			if(nxt==pre||nxt==idx)continue;
			dfs2(nxt,nxt,now);
		}
	}
};