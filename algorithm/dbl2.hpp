#include"../../kyopro_library/template.hpp"

template<typename SemiGroup,SemiGroup(*op)(SemiGroup,SemiGroup),int Log>
struct Doubling{
	Doubling(const vector<int>&p,const vector<SemiGroup>&v){
		int n=p.size();
		dat=vector<vector<SemiGroup>>(Log+1,vector<SemiGroup>(n));
		nxt=vector<vector<int>>(Log+1,vector<int>(n));
		for(int i=0;i<n;i++){
			dat[0][i]=v[i];
			nxt[0][i]=p[i];
		}
		for(int i=1;i<=Log;i++){
			for(int j=0;j<n;j++){
				nxt[i][j]=nxt[i-1][nxt[i-1][j]];
				dat[i][j]=op(dat[i-1][j],dat[i-1][nxt[i-1][j]]);
			}
		}
	}
	SemiGroup query(int start,ll k){
		SemiGroup ret=e();
		for(int b=0;k>0;b++,k>>=1){
			if(k&1){
				ret=op(ret,dat[b][start]);
				start=nxt[b][start];
			}
		}
		return ret;
	}
	int transition(int start,ll k){
		for(int b=0;k>0;b++,k>>=1)if(k&1)start=nxt[b][start];
		return start;
	}

private:
	vector<vector<SemiGroup>>dat;
	vector<vector<int>>nxt;
};