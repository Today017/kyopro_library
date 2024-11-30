#include"../../kyopro_library/template.hpp"

struct DsuRollback{
	DsuRollback()=default;
	DsuRollback(int n){
		par=vector<int>(n);
		sz=vector<int>(n);
		for(int i=0;i<n;i++){
			par[i]=i;
			sz[i]=1;
		}
	}
	int find(int x){
		if(par[x]==x)return x;
		return find(par[x]);
	}
	void merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y){
			history.push_back({x,-1,-1,-1});
			return;
		}
		if(sz[x]<sz[y])swap(x,y);
		history.push_back({x,y,sz[x],sz[y]});
		par[y]=x;
		sz[x]+=sz[y];
	}
	void undo(){
		if(history.empty())return;
		auto[x,y,szx,szy]=history.back();
		history.pop_back();
		if(y==-1)return;
		par[y]=y;
		sz[x]=szx;
		sz[y]=szy;
	}
	void snapshot(){history.clear();}
	void rollback(){while(!history.empty())undo();}
	bool same(int x,int y){return find(x)==find(y);}
	int size(int x){return sz[find(x)];}

private:
	vector<int>par,sz;
	vector<tuple<int,int,int,int>>history;
};
