#include "../../../kyopro_library/template.hpp"

// 辺属性 LCA
template<typename Monoid>
struct LcaEdge{
	using Type=typename Monoid::Type;

	LcaEdge(const vector<vector<pair<int,Type>>>&g,int root=0){
		int n=g.size();
		int k=1;
		while((1<<k)<n)k++;
		parent.assign(k,vector<int>(n,-1)),dep.assign(n,0),dat.assign(k,vector<Type>(n,Monoid::id()));
		dfs(g,root,-1);
		for(int i=0;i+1<k;i++){
			for(int j=0;j<n;j++){
				parent[i+1][j]=parent[i][j]==-1?-1:parent[i][parent[i][j]];
				dat[i+1][j]=parent[i][j]==-1?Monoid::id():Monoid::op(dat[i][j],dat[i][parent[i][j]]);
			}
		}
	}

	Type fold(int u,int v){
		if(dep[u]>dep[v])swap(u,v);
		Type ret=Monoid::id();
		while(dep[u]<dep[v]){
			int k=0;
			while((dep[v]-dep[u])>=(1<<(k+1)))k++;
			ret=Monoid::op(ret,dat[k][v]),v=parent[k][v];
		}
		while(u!=v){
			int k=0;
			while(parent[k+1][u]!=parent[k+1][v])k++;
			ret=Monoid::op(ret,dat[k][u]),ret=Monoid::op(ret,dat[k][v]);
			u=parent[k][u],v=parent[k][v];
		}
		return ret;
	}

private:
	vector<vector<int>>parent;
	vector<int>dep;
	vector<vector<Type>>dat;
	void dfs(const vector<vector<pair<int,Type>>>&g,int now,int pre){
		parent[0][now]=pre,dep[now]=pre==-1?0:dep[pre]+1;
		for(auto[nxt,cost]:g[now]){
			if(nxt==pre)continue;
			dat[0][nxt]=cost;
			dfs(g,nxt,now);
		}
	}
};

#include"../../../kyopro_library/others/monoid.hpp"