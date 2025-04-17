#include "../../../kyopro_library/template.hpp"

//頂点属性 LCA
template<typename Monoid>
struct LcaVtx{
	using Type=typename Monoid::Type;

	LcaVtx(const vector<vector<int>>&g,const vector<Type>&v,int root){
		int n=g.size();
		int k=1;
		while((1<<k)<n)k++;
		parent.assign(k,vector<int>(n,-1)),dep.assign(n,0),dat.assign(k,vector<Type>(n,Monoid::id()));
		dfs(g,v,root,-1,0);
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
			while(dep[v]-dep[u]>=(1<<(k+1)))k++;
			ret=Monoid::op(ret,dat[k][v]),v=parent[k][v];
		}
		while(u!=v){
			int k=0;
			while(parent[k+1][u]!=parent[k+1][v])k++;
			ret=Monoid::op(ret,dat[k][u]),ret=Monoid::op(ret,dat[k][v]);
			u=parent[k][u],v=parent[k][v];
		}
		ret=Monoid::op(ret,dat[0][u]);
		return ret;
	}

private:
	vector<vector<int>>parent;
	vector<int>dep;
	vector<vector<Type>>dat;
	void dfs(const vector<vector<int>>&g,const vector<Type>&v,int now,int par,int d){
		dat[0][now]=v[now],parent[0][now]=par,dep[now]=d;
		for(int nxt:g[now]){
			if(nxt==par)continue;
			dfs(g,v,nxt,now,d+1);
		}
	}
};

#include"../../../kyopro_library/others/monoid.hpp"