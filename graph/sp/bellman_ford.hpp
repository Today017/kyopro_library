#include"../../../kyopro_library/template.hpp"

/**
 * @brief ベルマンフォード法
 * @details 負の閉路が存在するか否かの bool 値と、各頂点までの最短距離を記録した配列の組を返す
 * @note O(VE)
 * @attention
 * 負閉路が存在する場合、最短経路が正しく計算されない場合がある。
 * このときは逆辺を張ったグラフで BFS 等を行い、目的の終点から到達可能である頂点を列挙し、
 * そのような頂点のみでベルマンフォード法を実行して調べる必要がある。
 * @ref https://yukicoder.me/submissions/967952
 * @ref https://mhrb-minase.hatenablog.com/entry/2019/08/20/003915
 */
pair<bool,vector<ll>>BellmanFord(const vector<vector<pair<int,ll>>>&g,int start){
	int n=g.size();
	vector<ll>dst(n,INFL);
	dst[start]=0;
	int i=0;
	for(;i<n;i++){
		bool update=false;
		for(int j=0;j<n;j++){
			for(auto[nxt,cost]:g[j]){
				if(dst[j]!=INFL&&dst[j]+cost<dst[nxt]){
					dst[nxt]=dst[j]+cost;
					update=true;
				}
			}
		}
		if(!update)break;
	}
	return{i==n,dst};
}