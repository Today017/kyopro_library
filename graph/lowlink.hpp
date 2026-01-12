#include"../../kyopro_library/template.hpp"

///@brief 橋と関節点の情報
struct BridgeInfo {
    vector<pair<int,int>> bridge; ///< 橋
    vector<int> articulation; ///< 関節点
};

///@brief Low Link のアルゴリズムによりグラフGの橋と関節点を求める
///@note O(V+E)
BridgeInfo LowLink(const vector<vector<int>>& g) {
    int n=g.size();
    vector<int> ord(n,-1), low(n,-1), articulation,seen(n,false);
    vector<pair<int,int>> bridge;

    auto dfs=[&](auto&& dfs, int now, int pre, int& cnt)-> void {
        seen[now]=true; ord[now]=low[now]=cnt++;
        bool is_articulation=false;
        int child=0;
        for(int nxt: g[now]) {
            if(!seen[nxt]) {
                child++;
                dfs(dfs,nxt,now,cnt);
                low[now]=min(low[now],low[nxt]);
                if(pre!=-1 && ord[now]<=low[nxt]) is_articulation=true;
                if(ord[now]<low[nxt]) bridge.push_back(minmax(now,nxt));
            }
            else if(nxt!=pre) low[now]=min(low[now],ord[nxt]);
        }
        if(pre==-1 && child>1) is_articulation=true;
        if(is_articulation) articulation.push_back(now);
    };

    int cnt=0;
    rep(i,n) if(!seen[i]) dfs(dfs,i,-1,cnt);
    sort(all(bridge));
    sort(all(articulation));
    return {bridge,articulation};
}