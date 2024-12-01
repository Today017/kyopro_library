#include"../../kyopro_library/template.hpp"

struct DsuRollback{
	DsuRollback()=default;
	DsuRollback(int n){
		par.resize(n);
		iota(par.begin(),par.end(),0);
		sz.assign(n,1);
		forest_count=n;
	}

	int find(int x){
		if(par[x]==x)return x;
		return find(par[x]);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y){
			history.push_back({x,-1,-1,-1});
			return false;
		}
		if(sz[x]<sz[y])swap(x,y);
		history.push_back({x,y,sz[x],sz[y]});
		par[y]=x;
		sz[x]+=sz[y];
		forest_count--;
		return true;
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
	int size(int x){return sz[find(x)];}
	bool same(int x,int y){return find(x)==find(y);}
	int count(){return forest_count;}
	vector<vector<int>>groups(){
		int n=par.size();
		vector<vector<int>>ret(n);
		for(int i=0;i<n;i++)ret[find(i)].push_back(i);
		ret.erase(remove_if(ret.begin(),ret.end(),[&](const vector<int>&v){return v.empty();}),ret.end());
		return ret;
	}

private:
	vector<int>par,sz;
	vector<tuple<int,int,int,int>>history;
	int forest_count;
};
