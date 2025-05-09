#include"../../../kyopro_library/template.hpp"

/// @brief LCA
struct LCA {
    /// @brief コンストラクタ
    LCA(const VVI& g, int root=0) {
        int n=g.size();
        int k=1;
        while((1<<k)<n) k++;
        par=VVI(k,VI(n,-1)),dep=VI(n);
        dfs(g,root,-1);
        REP(i,k-1) REP(j,n) par[i+1][j]=par[i][j]==-1?-1:par[i][par[i][j]];
    }
    
    /// @brief 頂点 u, v のLCAを返す
    int lca(int u, int v) {
        if(dep[u]<dep[v]) swap(u,v);
        int k=par.size();
        REP(i,k) if((dep[u]-dep[v])>>i&1) u=par[i][u];
        if(u==v) return u;
        FOR(i,k-1,-1) if(par[i][u]!=par[i][v]) u=par[0][u],v=par[0][v];
        return par[0][u];
    }

    /// @brief 頂点 u, v の距離を返す
    int distance(int u, int v) {
        return dep[u]+dep[v]-2*dep[lca(u,v)];
    }

    /// @brief 頂点 x が u-v のパス上にあるか否かを返す
    bool is_on_path(int u, int v, int x) {
        return distance(u,x)+distance(x,v)==distance(u,v);
    }

    /// @brief 頂点 u から d 回遡った位置にある頂点を返す
    int climb(int u, int d) {
        int k=par.size();
        FOR(i,k-1,-1) if(d>>i&1) u=par[i][u];
        return u;
    }

private:
    VVI par;
    VI dep;
    void dfs(const VVI& g, int now, int pre) {
        par[0][now]=pre,dep[now]=pre==-1?0:dep[pre]+1;
        for(int nxt:g[now]) if(nxt!=pre) dfs(g,nxt,now);
    }
};