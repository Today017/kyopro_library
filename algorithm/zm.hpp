#include"../../kyopro_library/template.hpp"

template<typename Monoid>
vector<typename Monoid::Type>zetaSubset(vector<typename Monoid::Type>v){
	int d=1;
	while((1<<d)<(int)v.size())d++; 
	for(int i=0;i<d;i++){
		for(int j=0;j<(int)v.size();j++){
			if(j>>i&1)v[j]=Monoid::op(v[j],v[j^(1<<i)]);
		}
	}
	return v;
}

template<typename Monoid>
vector<typename Monoid::Type>zetaSuperset(vector<typename Monoid::Type>v){
	int d=1;
	while((1<<d)<(int)v.size())d++; 
	for(int i=0;i<d;i++){
		for(int j=0;j<(int)v.size();j++){
			if(~j>>i&1)v[j]=Monoid::op(v[j],v[j^(1<<i)]);
		}
	}
	return v;
}