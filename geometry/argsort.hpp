#include"../../kyopro_library/template.hpp"

void argsort(vector<pair<ll,ll>>&xy){
	auto sign=[](pair<ll,ll>p){
		auto[x,y]=p;
		if(x==0&&y==0)return 0;
		if(y<0||(y<=0&&x>0))return -1;
		return 1;
	};
	sort(xy.begin(),xy.end(),[&](pair<ll,ll>l,pair<ll,ll>r){
		if(sign(l)!=sign(r))return sign(l)<sign(r);
		return l.first*r.second<l.second*r.first;
	});
}