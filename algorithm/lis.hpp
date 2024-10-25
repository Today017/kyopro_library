#include"../../kyopro_library/template.hpp"

int lisLength(vector<int>&a,bool strict=true){
	int n=a.size();
	vector<int>dp(n,INF);
	for(int i=0;i<n;i++){
		auto itr=strict?lower_bound(dp.begin(),dp.end(),a[i]):upper_bound(dp.begin(),dp.end(),a[i]);
		*itr=a[i];
	}
	return find(dp.begin(),dp.end(),INF)-dp.begin();
}