#include"../../kyopro_library/template.hpp"

template<typename Band>
struct SparseTable{
	using Type=typename Band::Type;

	SparseTable()=default;
	SparseTable(const vector<Type>&v){
		n=v.size();
		dat.assign(__lg(n)+1,vector<Type>(n));
		dat[0]=v;
		for(int i=1;i<(int)dat.size();i++){
			for(int j=0;j+(1<<i)<=n;j++){
				dat[i][j]=Band::op(dat[i-1][j],dat[i-1][j+(1<<(i-1))]);
			}
		}
	}
	Type fold(int l,int r){
		r--;
		int i=__lg(r-l+1);
		return Band::op(dat[i][l],dat[i][r-(1<<i)+1]);
	}

	int size(){return n;}
	Type operator[](int i)const{return fold(i,i+1);}

private:
	int n;
	vector<vector<Type>>dat;
};