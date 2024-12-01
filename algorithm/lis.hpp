#include"../../kyopro_library/template.hpp"

int lisLength(vector<int>&v,bool strict=true){
	int n=v.size();
	vector<int>dp(n,INF);
	for(int i=0;i<n;i++){
		auto itr=strict?lower_bound(dp.begin(),dp.end(),v[i]):upper_bound(dp.begin(),dp.end(),v[i]);
		*itr=v[i];
	}
	return find(dp.begin(),dp.end(),INF)-dp.begin();
}