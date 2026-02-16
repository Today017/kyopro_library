#include"../../kyopro_library/template.hpp"

///@brief 二部グラフに対し、01の色分けをする
///@brief 二部グラフでない場合は空の配列を返す
vector<int> BiColorize(const vector<vector<int>>& g) {
    int n=g.size();
    vector<int> col(n,-1);
    queue<int> que;
    rep(i,n) if(col[i]==-1) {
        col[i]=0;
        que.push(i);
        while(!que.empty()) {
            int now=que.front(); que.pop();
            for(int nxt: g[now]) {
                int c=col[now]^1;
                if(col[nxt]==-1) {
                    col[nxt]=c;
                    que.push(nxt);
                } else if(col[nxt]!=c) {
                    return {};
                }
            }
        }
    }
    return col;
}