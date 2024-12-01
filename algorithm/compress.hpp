#include"../../kyopro_library/template.hpp"

template<typename T>
vector<ll>compress(vector<T>&v){
	int n=v.size();
	vector<ll>ret(n);
	for(int i=0;i<n;i++)ret[i]=v[i];
	sort(ret.begin(),ret.end());
	ret.erase(unique(ret.begin(),ret.end()),ret.end());
	for(int i=0;i<n;i++)v[i]=lower_bound(ret.begin(),ret.end(),v[i])-ret.begin();
	return ret;
}