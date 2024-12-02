#pragma once
#include "../../kyopro_library/template.hpp"

template<typename T>
struct FenwickTreeBaseAbel{
	using Type=T;
	static Type id(){return 0;}
	static Type op(Type a,Type b){return a+b;}
	static Type inv(Type a){return-a;}
};

template<typename Abel=FenwickTreeBaseAbel<ll>>
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
