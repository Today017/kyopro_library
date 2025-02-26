#include"../../kyopro_library/template.hpp"

namespace ZetaMobius{
	// 高速ゼータ変換（下位集合）
	// v'[s] = Σ_{t⊆s} v[t] なる v' を返す。
	// |v| = 2^n として O(n 2^n)
	template<typename Monoid>
	vector<typename Monoid::Type>subset_zeta(vector<typename Monoid::Type>v){
		int d=1;
		while((1<<d)<(int)v.size())d++; 
		for(int i=0;i<d;i++){
			for(int j=0;j<(int)v.size();j++){
				if(j>>i&1)v[j]=Monoid::op(v[j],v[j^(1<<i)]);
			}
		}
		return v;
	}

	// 高速ゼータ変換（上位集合）
	// v'[s] = Σ_{t⊇s} v[t] なる v' を返す。
	// |v| = 2^n として O(n 2^n)
	template<typename Monoid>
	vector<typename Monoid::Type>superset_zeta(vector<typename Monoid::Type>v){
		int d=1;
		while((1<<d)<(int)v.size())d++; 
		for(int i=0;i<d;i++){
			for(int j=0;j<(int)v.size();j++){
				if(~j>>i&1)v[j]=Monoid::op(v[j],v[j^(1<<i)]);
			}
		}
		return v;
	}

	// 高速メビウス変換（下位集合）
	// v[s] = Σ_{t⊆s} v'[t] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// |v| = 2^n として O(n 2^n)
	template<typename Abel>
	vector<typename Abel::Type>subset_mobius(vector<typename Abel::Type>v){
		int d=1;
		while((1<<d)<(int)v.size())d++;
		for(int i=0;i<d;i++){
			for(int j=0;j<(int)v.size();j++){
				if(j>>i&1)v[j]=Abel::op(v[j],Abel::inv(v[j^(1<<i)]));
			}
		}
		return v;
	}

	// 高速メビウス変換（上位集合）
	// v[s] = Σ_{t⊇s} v'[t] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// |v| = 2^n として O(n 2^n)
	template<typename Abel>
	vector<typename Abel::Type>superset_mobius(vector<typename Abel::Type>v){
		int d=1;
		while((1<<d)<(int)v.size())d++;
		for(int i=0;i<d;i++){
			for(int j=0;j<(int)v.size();j++){
				if(~j>>i&1)v[j]=Abel::op(v[j],Abel::inv(v[j^(1<<i)]));
			}
		}
		return v;
	}
}

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/abel.hpp"