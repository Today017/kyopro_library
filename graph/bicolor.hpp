#include"../../kyopro_library/template.hpp"

///@brief 二部グラフに対し、01の色分けをする
///@brief 二部グラフでない場合は空の配列を返す
vector<int> BiColorize(const vector<vector<int>>& G) {
    int N=G.size();
    vector<int> col(N,-1);
    queue<int> que;
    rep(i,N) if(col[i]==-1) {
        col[i]=0;
        que.push(i);
        while(!que.empty()) {
            int now=que.front(); que.pop();
            for(int nxt: G[now]) {
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