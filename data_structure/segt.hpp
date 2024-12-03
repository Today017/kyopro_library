#pragma once
#include"../../kyopro_library/template.hpp"

template<typename Monoid>
struct SegTree{
	using Type=typename Monoid::Type;

	SegTree()=default;
	SegTree(int n){
		this->n=n;
		dat.assign(n<<1,Monoid::id());
	}
	SegTree(const vector<Type>&v){
		this->n=v.size();
		dat.assign(n<<1,Monoid::id());
		for(int i=0;i<n;i++)dat[i+n]=v[i];
		for(int i=n-1;i>0;i--)dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
	}

	void set(int i,Type x){
		i+=n;
		dat[i]=x;
		while(i>>=1)dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
	}
	Type fold(int l,int r){
		Type retl=Monoid::id(),retr=Monoid::id();
		l+=n,r+=n;
		while(l<r){
			if(l&1)retl=Monoid::op(retl,dat[l++]);
			if(r&1)retr=Monoid::op(dat[--r],retr);
			l>>=1,r>>=1;
		}
		return Monoid::op(retl,retr);
	}
	template<typename F>
	int find_right(int l,F f){
		assert(f(Monoid::id()));
		if(l==n)return n;
		l+=n;
		int r=n+n;
		vector<int>cand_l,cand_r;
		while(l<r){
			if(l&1)cand_l.push_back(l++);
			if(r&1)cand_r.push_back(--r);
			l>>=1,r>>=1;
		}
		vector<int>cand=cand_l;
		reverse(cand_r.begin(),cand_r.end());
		cand.insert(cand.end(),cand_r.begin(),cand_r.end());
		Type val=Monoid::id();
		for(int i:cand){
			if(f(Monoid::op(val,dat[i]))){
				val=Monoid::op(val,dat[i]);
			}else{
				while(i<n){
					i<<=1;
					if(f(Monoid::op(val,dat[i]))){
						val=Monoid::op(val,dat[i]);
						i|=1;
					}
				}
				return i-n;
			}
		}
		return n;
	}
	template<typename F>
	int find_left(int r,F f){
		assert(f(Monoid::id()));
		if(r==0)return 0;
		r+=n;
		int l=n;
		vector<int>cand_l,cand_r;
		while(l<r){
			if(l&1)cand_l.push_back(l++);
			if(r&1)cand_r.push_back(--r);
			l>>=1,r>>=1;
		}
		vector<int>cand=cand_r;
		reverse(cand_l.begin(),cand_l.end());
		cand.insert(cand.end(),cand_l.begin(),cand_l.end());
		Type val=Monoid::id();
		for(int i:cand){
			if(f(Monoid::op(dat[i],val))){
				val=Monoid::op(dat[i],val);
			}else{
				while(i<n){
					i=(i<<1)|1;
					if(f(Monoid::op(dat[i],val))){
						val=Monoid::op(dat[i],val);
						i^=1;
					}
				}
				return i-n+1;
			}
		}
		return 0;
	}

	int size(){return n;}
	Type operator[](int i){return dat[i+n];}

private:
	int n;
	vector<Type>dat;
};

#include"../../kyopro_library/others/monoid.hpp"

template<typename T,T max_value=INF>
struct RangeMin{using Type=struct SegTree<MinMonoid<T,max_value>>;};

template<typename T,T min_value=-INF>
struct RangeMax{using Type=struct SegTree<MaxMonoid<T,min_value>>;};

template<typename T>
struct RangeSum{using Type=struct SegTree<SumMonoid<T>>;};


