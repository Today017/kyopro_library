#include"../../../kyopro_library/template.hpp"

VL BFS(const VVI&g, int start=0){
	int n=g.size();
	VL ret(n,-1);
	queue<int> que;
	que.push(start);
	ret[start]=0;

	while(!que.empty()){
		int now=que.front();que.pop();

		for(int nxt:g[now])if(ret[nxt]==-1) ret[nxt]=ret[now]+1,que.push(nxt);
	}

	return ret;
}