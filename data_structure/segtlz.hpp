#pragma once
#include"../../kyopro_library/template.hpp"

template<typename T,typename U>
struct SegmentTreeLazy{
	using F=function<T(T,T)>;
	using G=function<T(U,T)>;
	using H=function<U(U,U)>;
	SegmentTreeLazy()=default;
	SegmentTreeLazy(int n,F f,G g,H h,T et,U eu){
		this->n=1;
		while(this->n<n)this->n*=2;
		this->f=f;
		this->g=g;
		this->h=h;
		this->et=et;
		this->eu=eu;
		dat=vector<T>(this->n*2-1,et);
		lazy=vector<U>(this->n*2-1,eu);
	}
	void build(const vector<T>&a){
		for(int i=0;i<(int)a.size();i++)dat[i+n-1]=a[i];
		for(int i=n-2;i>=0;i--)dat[i]=f(dat[i*2+1],dat[i*2+2]);
	}
	void set(int i,T x){
		evaluate(i);
		i+=n-1;
		dat[i]=x;
		while(i>0){
			i=(i-1)/2;
			dat[i]=f(dat[i*2+1],dat[i*2+2]);
		}
	}
	void apply(int l,int r,U x){apply(l,r,0,x,0,n);}
	T query(int l,int r){return query(l,r,0,0,n);}
	T operator[](int i){return query(i,i+1,0,0,n);}
	int size(){return n;}

private:
	int n;
	vector<T>dat;
	vector<U>lazy;
	F f;
	G g;
	H h;
	T et;
	U eu;
	void evaluate(int i){
		if(lazy[i]==eu)return;
		if(i<n-1){
			lazy[i*2+1]=h(lazy[i],lazy[i*2+1]);
			lazy[i*2+2]=h(lazy[i],lazy[i*2+2]);
		}
		dat[i]=g(lazy[i],dat[i]);
		lazy[i]=eu;
	}
	void apply(int left,int right,int i,U x,int l,int r){
		evaluate(i);
		if(left<=l&&r<=right){
			lazy[i]=h(x,lazy[i]);
			evaluate(i);
		}else if(left<r&&l<right){
			int mid=(l+r)/2;
			apply(left,right,i*2+1,x,l,mid);
			apply(left,right,i*2+2,x,mid,r);
			dat[i]=f(dat[i*2+1],dat[i*2+2]);
		}
	}
	T query(int left,int right,int i,int l,int r){
		evaluate(i);
		if(r<=left||right<=l){
			return et;
		}else if(left<=l&&r<=right){
			return dat[i];
		}else{
			int mid=(l+r)/2;
			return f(query(left,right,i*2+1,l,mid),query(left,right,i*2+2,mid,r));
		}
	}
};

//verified
template<typename T,typename U>
SegmentTreeLazy<T,U>RangeAddRangeMin(int n,T max_value){
	const T et=max_value;
	const U eu=0;
	auto f=[](T a,T b){return min(a,b);};
	auto g=[](U f,T x){return f+x;};
	auto h=[](U f,U g){return f+g;};
	return SegmentTreeLazy<T,U>(n,f,g,h,et,eu);
}

template<typename T,typename U>
SegmentTreeLazy<T,U>RangeAddRangeMax(int n,T min_value){
	const T et=min_value;
	const U eu=0;
	auto f=[](T a,T b){return max(a,b);};
	auto g=[](U f,T x){return f+x;};
	auto h=[](U f,U g){return f+g;};
	return SegmentTreeLazy<T,U>(n,f,g,h,et,eu);
}

//verified
template<typename T,typename U>
SegmentTreeLazy<pair<T,int>,U>RangeAddRangeSum(int n){
	using T2=pair<T,int>;
	const T2 et=make_pair(T(0),0);
	const U eu=0;
	auto f=[](T2 a,T2 b){return make_pair(a.first+b.first,a.second+b.second);};
	auto g=[](U f,T2 x){return make_pair(x.first+(T)f*x.second,x.second);};
	auto h=[](U f,U g){return f+g;};
	return SegmentTreeLazy<T2,U>(n,f,g,h,et,eu);
}

//verified
template<typename T>
SegmentTreeLazy<T,T>RangeUpdateRangeMin(int n,T max_value,T not_exist){
	const T et=max_value;
	const T eu=not_exist;
	auto f=[](T a,T b){return min(a,b);};
	auto g=[eu](T f,T x){
		if(f==eu)return x;
		return f;
	};
	return SegmentTreeLazy<T,T>(n,f,g,g,et,eu);
}

template<typename T>
SegmentTreeLazy<T,T>RangeUpdateRangeMax(int n,T min_value,T not_exist){
	const T et=min_value;
	const T eu=not_exist;
	auto f=[](T a,T b){return max(a,b);};
	auto g=[eu](T f,T x){
		if(f==eu)return x;
		return f;
	};
	return SegmentTreeLazy<T,T>(n,f,g,g,et,eu);
}

template<typename T>
SegmentTreeLazy<pair<T,int>,T>RangeUpdateRangeSum(int n,T not_found){
	using T2=pair<T,int>;
	const T2 et=make_pair(T(0),0);
	const T eu=not_found;
	auto f=[](T2 a,T2 b){return make_pair(a.first+b.first,a.second+b.second);};
	auto g=[eu](T f,T2 x){
		if(f==eu)return x;
		return make_pair(f*x.second,x.second);
	};
	auto h=[eu](T f,T g){
		if(f==eu)return g;
		return f;
	};
	return SegmentTreeLazy<pair<T,int>,T>(n,f,g,h,et,eu);
}