#include "../../kyopro_library/template.hpp"

template<typename Group>
struct DsuPotentialized{
	using Type=typename Group::Type;

	DsuPotentialized()=default;
	DsuPotentialized(int n){
		par.resize(n);
		iota(par.begin(),par.end(),0);
		sz.assign(n,1);
		diff_weight.assign(n,Group::id());
        forest_count=n;
	}

	int find(int x){
		if(par[x]==x)return x;
		int root=find(par[x]);
		diff_weight[x]=Group::op(diff_weight[x],diff_weight[par[x]]);
		return par[x]=root;
	}
	bool merge(int x,int y,Type w){
		w=Group::op(Group::inv(weight(y)),Group::op(w,weight(x)));
		x=find(x),y=find(y);
		if(x==y)return false;
		if(sz[x]<sz[y]){
			swap(x,y);
			w=Group::inv(w);
		}
		par[y]=x;
		sz[x]+=sz[y];
		diff_weight[y]=w;
        forest_count--;
		return true;
	}
	Type weight(int x){
		find(x);
		return diff_weight[x];
	}
	Type diff(int x,int y){return Group::op(diff_weight[y],Group::inv(diff_weight[x]));}
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
	vector<Type>diff_weight;
    int forest_count;
};