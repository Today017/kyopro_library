#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/scc.hpp"

//2-SAT
struct TwoSat{
	vector<vector<int>>G;
	TwoSat(int n){G.assign(2*n,vector<int>());}

	//(i==fi || j==fj) を追加
	void add(int i,bool fi,int j,bool fj){
		// 2i = i が true, 2i+1 = i が false
		i=2*i+!fi,j=2*j+!fj;
		// !i -> j, !j -> i
		G[i^1].push_back(j),G[j^1].push_back(i);
	}

	//unsatisfiable なら空の vector を返す
	vector<bool>solve(){
		auto[mem,ng,gr]=SccDecomposition(G);
		int n=G.size()/2;
		vector<bool>ret(n);
		for(int i=0;i<n;i++){
			if(gr[i*2]==gr[i*2+1])return vector<bool>();
			// 2i(true) が後ろなら i は true
			ret[i]=gr[i*2]>gr[i*2+1];
		}
		return ret;
	}
};
