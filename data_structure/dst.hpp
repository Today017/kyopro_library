#include "../../kyopro_library/template.hpp"

template<typename Semigroup>
struct DisjointSparseTable{
	using Type=typename Semigroup::Type;

	DisjointSparseTable()=default;
	DisjointSparseTable(const vector<Type>&v){
		n=v.size();
		dat.assign(__lg(n)+1,vector<Type>(n));
		dat[0]=v;
		for(int i=1;i<(int)dat.size();i++){
			int w=1<<i;
			for(int j=0;j<n;j+=w<<1){
				int t=min(j+w,n);
				dat[i][t-1]=v[t-1];
				for(int k=t-2;k>=j;k--)dat[i][k]=Semigroup::op(v[k],dat[i][k+1]);
				if(t>=n)break;
				dat[i][t]=v[t];
				for(int k=t+1;k<min(j+(w<<1),n);k++)dat[i][k]=Semigroup::op(dat[i][k-1],v[k]);
			}
		}
	}
	Type fold(int l,int r){
		r--;
		if(l==r)return dat[0][l];
		int i=__lg(l^r);
		return Semigroup::op(dat[i][l],dat[i][r]);
	}

	int size(){return n;}
	Type operator[](int i)const{return fold(i,i+1);}

private:
	int n;
	vector<vector<Type>>dat;
};