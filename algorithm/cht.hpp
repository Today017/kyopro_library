#include"../../kyopro_library/template.hpp"

//Convex Hull Trick
//verify: https://judge.yosupo.jp/problem/line_add_get_min
//ref: https://hcpc-hokudai.github.io/archive/algorithm_convex_hull_trick_001.pdf
template<typename T=ll,bool Min=true>
struct CHT{
	CHT()=default;
	void add(T a,T b){
		if(!Min){
			a*=-1;
			b*=-1;
		}
		if(lines.count(a)&&lines[a]<=b)return;
		lines[a]=b;
		auto it=lines.find(a);
		if(!need(it)){
			lines.erase(a);
			return;
		}
		if(it!=lines.begin()){
			it=prev(it);
			while(true){
				if(need(it))break;
				auto prv=prev(it);
				lines.erase(it);
				it=prv;
			}
		}
		it=next(lines.find(a));
		while(true){
			if(need(it))break;
			auto nxt=next(it);
			lines.erase(it);
			it=nxt;
		}
	}
	T get(T x){
		T lo=lines.begin()->first,hi=lines.rbegin()->first+1;
		while(hi-lo>1){
			T mid=(lo+hi)/2;
			auto it=lines.lower_bound(mid);
			if(it==lines.begin()){
				lo=mid;
				continue;
			}
			if(it==lines.end()){
				hi=mid;
				continue;
			}
			auto[a1,b1]=*prev(it);
			auto[a2,b2]=*it;
			(a1*x+b1<=a2*x+b2?hi:lo)=mid;
		}
		auto it=lines.lower_bound(lo);
		auto[a,b]=*it;
		return(a*x+b)*(Min?1:-1);
	}

private:
	map<T,T>lines;
	bool need(const typename map<T,T>::iterator it){
		if(it==lines.begin()||it==prev(lines.end())||it==lines.end())return true;
		auto prv=prev(it);
		auto nxt=next(it);
		auto[a,b]=*it;
		auto[a1,b1]=*nxt;
		auto[a2,b2]=*prv;
		return(__int128_t)(a1-a)*(b-b2)<(__int128_t)(a-a2)*(b1-b);
	}
};