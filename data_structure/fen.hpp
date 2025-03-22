#pragma once
#include "../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/abel.hpp"

template<typename Abel=Abel::Sum<ll>>
struct FenwickTree{
	using Type=typename Abel::Type;

	FenwickTree()=default;
	FenwickTree(int n){
		this->n=n;
		dat.assign(n,Abel::id());
	}

	void add(int i,Type x){
		i++;
		while(i<=n){
			dat[i-1]=Abel::op(dat[i-1],x);
			i+=i&-i;
		}
	}

	Type sum(int l,int r){return Abel::op(Abel::inv(sum(l)),sum(r));}

	Type operator[](int i){return sum(i,i+1);}
	int size(){return n;}

private:
	int n;
	vector<Type>dat;
	Type sum(int r){
		Type ret=Abel::id();
		while(r>0){
			ret=Abel::op(ret,dat[r-1]);
			r-=r&-r;
		}
		return ret;
	}
};
