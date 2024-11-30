#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/dsur.hpp"

struct DynamicConnectivity{
	using P=pair<int,int>;
	DsuRollback dsu;
	int n;
	vector<vector<P>>edges;
	vector<pair<P,P>>period;
	map<P,int>count,appear;
	DynamicConnectivity(int v,int q){
		n=q;
		edges=vector<vector<P>>(2*n);
		dsu=DsuRollback(v);
	}
	void merge(int idx,int u,int v){
		P e=minmax(u,v);
		if(count[e]++==0)appear[e]=idx;
	}
	void purge(int idx,int u,int v){
		P e=minmax(u,v);
		if(--count[e]==0)period.push_back({{appear[e],idx},e});
	}
	void build(){
		for(auto[e,val]:count){
			if(val>0)period.push_back({{appear[e],n},e});
		}
		for(auto[range,e]:period){
			auto[l,r]=range;
			l+=n,r+=n;
			while(l<r){
				if(l&1) edges[l++].push_back(e);
				if(r&1) edges[--r].push_back(e);
				l/=2,r/=2;
			}
		}
	}
	void execute(auto &f, int k=1){
		if(k>=2*n)return;
		for(auto[u,v]:edges[k])dsu.merge(u,v);
		if(k<n){
			execute(f,k<<1);
			execute(f,k<<1|1);
		}else if(0<=k-n&&k-n<n){
			int query_idx=k-n;
			f(query_idx);
		}
		for(auto[u,v]:edges[k])dsu.undo();
	}
};
