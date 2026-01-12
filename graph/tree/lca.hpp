#include"../../../kyopro_library/template.hpp"

///@brief LCA
///@ref verify: https://onlinejudge.u-aizu.ac.jp/status/users/Today03/submissions/1/GRL_5_C/judge/10572843/C++17
struct LCA {
    LCA(const vector<vector<int>>& g, int root=0) {
        int n=g.size(), k=1;
        while((1<<k)<n) k++;
        par=vector<vector<int>>(k,vector<int>(n,-1)),dep=vector<int>(n);
        dfs(g,root,-1);
        rep(i,k-1) rep(j,n) par[i+1][j]=(par[i][j]==-1?-1:par[i][par[i][j]]);
    }

    int lca(int u, int v) {
        if(dep[u]<dep[v]) swap(u,v);
        int k=par.size();
        rep(i,k) if((dep[u]-dep[v])>>i&1) u=par[i][u];
        if(u==v) return u;
        for(int i=k-1; i>=0; i--) if(par[i][u]!=par[i][v]) u=par[i][u], v=par[i][v];
        return par[0][u];
    }

    int distance(int u, int v) { return dep[u]+dep[v]-2*dep[lca(u,v)]; }

    bool is_on_path(int u, int v, int x) { return distance(u,x)+distance(x,v)==distance(u,v); }

    int climb(int u, int d) {
        int k=par.size();
        for(int i=k-1; i>=0; i--) if(d>>i&1) u=par[i][u];
        return u;
    }

    vector<vector<int>> par;
    vector<int> dep;

private:
    void dfs(const vector<vector<int>>& g, int now, int pre) {
        par[0][now]=pre; dep[now]=(pre==-1 ? 0 : dep[pre]+1);
        for(int nxt: g[now]) if(nxt!=pre) dfs(g,nxt,now);
    }
};
