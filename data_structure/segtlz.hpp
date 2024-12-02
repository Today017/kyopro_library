#pragma once
#include"../../kyopro_library/template.hpp"

template<typename Monoid,typename Operator,auto mapping>
struct SegTreeLazy{
	using MonoidType=typename Monoid::Type;
	using OperatorType=typename Operator::Type;

	SegTreeLazy()=default;
	SegTreeLazy(int n){
		this->n=n;
		dat.assign(n<<1,Monoid::id());
		lazy.assign(n<<1,Operator::id());
	}
	SegTreeLazy(const vector<MonoidType>&v){
		this->n=v.size();
		dat.assign(n<<1,Monoid::id());
		lazy.assign(n<<1,Operator::id());
		for(int i=0;i<n;i++)dat[i+n]=v[i];
		for(int i=n-1;i>0;i--)dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
	}

	void set(int i,MonoidType x){
		generate_indices(i,i+1);
		pushdown();
		i+=n;
		dat[i]=x;
		while(i>>=1)dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
	}
	void apply(int l,int r,OperatorType x){
		generate_indices(l,r);
		pushdown();
		l+=n,r+=n;
		while(l<r){
			if(l&1){
				lazy[l]=Operator::op(lazy[l],x);
				dat[l]=mapping(dat[l],x);
				l++;
			}
			if(r&1){
				r--;
				lazy[r]=Operator::op(lazy[r],x);
				dat[r]=mapping(dat[r],x);
			}
			l>>=1,r>>=1;
		}
		pushup();
	}
	MonoidType fold(int l,int r){
		generate_indices(l,r);
		pushdown();
		MonoidType retl=Monoid::id(),retr=Monoid::id();
		l+=n,r+=n;
		while(l<r){
			if(l&1)retl=Monoid::op(retl,dat[l++]);
			if(r&1)retr=Monoid::op(dat[--r],retr);
			l>>=1,r>>=1;
		}
		return Monoid::op(retl,retr);
	}

	int size(){return n;}
	MonoidType operator[](int i){return fold(i,i+1);}

private:
	int n;
	vector<MonoidType>dat;
	vector<OperatorType>lazy;
	vector<int>indices;
	void generate_indices(int l,int r){
		indices.clear();
		l+=n,r+=n;
		int lm=(l/(l&-l))>>1,rm=(r/(r&-r))>>1;
		while(l<r){
			if(l<=lm)indices.push_back(l);
			if(r<=rm)indices.push_back(r);
			l>>=1,r>>=1;
		}
		while(l){
			indices.push_back(l);
			l>>=1;
		}
	}
	void pushdown(){
		for(int j=(int)indices.size()-1;j>=0;j--){
			int i=indices[j];
			if(i<n){
				lazy[i<<1]=Operator::op(lazy[i<<1],lazy[i]);
				lazy[i<<1|1]=Operator::op(lazy[i<<1|1],lazy[i]);
				dat[i<<1]=mapping(dat[i<<1],lazy[i]);
				dat[i<<1|1]=mapping(dat[i<<1|1],lazy[i]);
			}
			lazy[i]=Operator::id();
		}
	}
	void pushup(){
		for(int j=0;j<(int)indices.size();j++){
			int i=indices[j];
			dat[i]=Monoid::op(dat[i<<1],dat[i<<1|1]);
		}
	}
};

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/operator.hpp"

template<typename T,T max_value,T not_exist>
struct RangeUpdateRangeMin{
	static T mapping(const T&a,const T&b){return b==not_exist?a:b;}
	using Type=struct SegTreeLazy<MinMonoid<T,max_value>,UpdateOperator<T,not_exist>,mapping>;
};

template<typename T,T min_value,T not_exist>
struct RangeUpdateRangeMax{
	static T mapping(const T&a,const T&b){return b==not_exist?a:b;}
	using Type=struct SegTreeLazy<MaxMonoid<T,min_value>,UpdateOperator<T,not_exist>,mapping>;
};

template<typename T,T not_exist>
struct RangeUpdateRangeSum{
	using S=typename PairSumMonoid<T>::Type;
	static S mapping(const S&a,const T&b){return b==not_exist?a:S{b*a.second,a.second};}
	using Type=struct SegTreeLazy<PairSumMonoid<T>,UpdateOperator<T,not_exist>,mapping>;
};

template<typename T,T max_value>
struct RangeAddRangeMin{
	static T mapping(const T&a,const T&b){return a+b;}
	using Type=struct SegTreeLazy<MinMonoid<T,max_value>,AddOperator<T>,mapping>;
};

template<typename T,T min_value>
struct RangeAddRangeMax{
	static T mapping(const T&a,const T&b){return a+b;}
	using Type=struct SegTreeLazy<MaxMonoid<T,min_value>,AddOperator<T>,mapping>;
};

template<typename T>
struct RangeAddRangeSum{
	using S=typename PairSumMonoid<T>::Type;
	static S mapping(const S&a,const T&b){return{a.first+b*a.second,a.second};}
	using Type=struct SegTreeLazy<PairSumMonoid<T>,AddOperator<T>,mapping>;
};
