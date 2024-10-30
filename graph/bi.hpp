#include"../../kyopro_library/template.hpp"

//O(nm)
vector<pair<int,int>> bipartiteMatching(const vector<vector<int>>&g){
	int n=g.size();
	vector<int>match(n,-1);
	vector<bool>used(n);

	auto dfs=[&](auto dfs,int now)->bool{
		used[now]=true;
		for(int nxt:g[now]){
			if(match[nxt]==-1||!used[match[nxt]]&&dfs(dfs,match[nxt])){
				match[now]=nxt;
				match[nxt]=now;
				return true;
			}
		}
		return false;
	};

	for(int i=0;i<n;i++){
		if(match[i]==-1){
			fill(used.begin(),used.end(),false);
			dfs(dfs,i);
		}
	}

	vector<pair<int,int>>ret;
	for(int i=0;i<n;i++){
		if(match[i]>i&&match[match[i]]==i)ret.push_back({i,match[i]});
	}
	return ret;
}

struct BiInfo{
	int max_matching,min_edge_cover,max_independent_set,min_vertex_cover;
};

BiInfo biInfo(const vector<vector<int>>&g){
	int n=g.size();
	int isolation=0;
	for(int i=0;i<n;i++)if((int)g[i].size()==0)isolation++;

	BiInfo ret;
	int m=bipartiteMatching(g).size();
	ret.max_matching=m;
	ret.min_edge_cover=isolation==0?n-m:-1;
	ret.min_vertex_cover=m;
	ret.max_independent_set=n-m;

	return ret;
}

