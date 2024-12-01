#include "../../kyopro_library/template.hpp"

struct DsuBaseSemigroup{
	using Type=ll;
	static Type op(Type a,Type b){return a+b;}
};

template<typename CommutativeSemigroup=DsuBaseSemigroup>
struct DsuMerging{
	using Type=typename CommutativeSemigroup::Type;

	DsuMerging()=default;
	DsuMerging(int n,const vector<Type>&v){
		par.resize(n);
		iota(par.begin(),par.end(),0);
		sz.assign(n,1);
		dat=v;
		forest_count=n;
	}

	int find(int x){
		if(par[x]==x)return x;
		return par[x]=find(par[x]);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return false;
		if(sz[x]<sz[y])swap(x,y);
		par[y]=x;
		sz[x]+=sz[y];
		dat[x]=CommutativeSemigroup::op(dat[x],dat[y]);
		forest_count--;
	}
	Type get(int x){return dat[find(x)];}
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
	vector<Type>dat;
	int forest_count;
};