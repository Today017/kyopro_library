#include"../../kyopro_library/template.hpp"

template<int Log>
struct Doubling{
	Doubling(const vector<int>&v){
		int n=v.size();
		nxt.assign(Log+1,vector<int>(n));
		for(int i=0;i<n;i++)nxt[0][i]=v[i];
		for(int i=0;i<Log;i++){
			for(int j=0;j<n;j++)nxt[i+1][j]=nxt[i][nxt[i][j]];
		}
	}

	int next(int start,ll k){
		for(int b=0;k>0;b++,k>>=1)if(k&1)start=nxt[b][start];
		return start;
	}

private:
	vector<vector<int>>nxt;
};