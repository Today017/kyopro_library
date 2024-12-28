#include "../../kyopro_library/template.hpp"

struct DsuBaseSemigroup{
	using Type=ll;
	static Type op(Type a,Type b){return a+b;}
};

template<typename Semigroup=DsuBaseSemigroup>
struct DsuMerging{
	using Type=typename Semigroup::Type;

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
		if(sz[x]>=sz[y]){
			par[y]=x;
			sz[x]+=sz[y];
			dat[x]=Semigroup::op(dat[x],dat[y]);
		}else{
			par[x]=y;
			sz[y]+=sz[x];
			dat[y]=Semigroup::op(dat[x],dat[y]);
		}
		forest_count--;
		return true;
	}
	const Type& get(int x){return dat[find(x)];}
	int size(int x)const{return sz[find(x)];}
	bool same(int x,int y)const{return find(x)==find(y);}
	int count()const{return forest_count;}
	vector<vector<int>>groups()const{
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
