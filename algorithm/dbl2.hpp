#include"../../kyopro_library/template.hpp"

template<typename Monoid,int Log>
struct Doubling{
	using Type=typename Monoid::Type;

	Doubling(const vector<int>&p,const vector<Type>&v){
		int n=p.size();
		dat.assign(Log+1,vector<Type>(n,Monoid::id()));
		nxt.assign(Log+1,vector<int>(n));
		for(int i=0;i<n;i++){
			dat[0][i]=v[i];
			nxt[0][i]=p[i];
		}
		for(int i=1;i<=Log;i++){
			for(int j=0;j<n;j++){
				nxt[i][j]=nxt[i-1][nxt[i-1][j]];
				dat[i][j]=Monoid::op(dat[i-1][j],dat[i-1][nxt[i-1][j]]);
			}
		}
	}

	Type fold(int start,ll k){
		Type ret=Monoid::id();
		for(int b=0;k>0;b++,k>>=1){
			if(k&1){
				ret=Monoid::op(ret,dat[b][start]);
				start=nxt[b][start];
			}
		}
		return ret;
	}
	int next(int start,ll k){
		for(int b=0;k>0;b++,k>>=1)if(k&1)start=nxt[b][start];
		return start;
	}

private:
	vector<vector<Type>>dat;
	vector<vector<int>>nxt;
};