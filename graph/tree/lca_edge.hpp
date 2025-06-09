#include "../../../kyopro_library/template.hpp"

/// @brief 辺属性LCA
template<typename Monoid>
struct LcaEdge {
    using Type=typename Monoid::Type;

    /// @brief コンストラクタ
    /// @param g 重み付き木
    LcaEdge(const vector<vector<pair<int,Type>>>& g, int root=0) {
        int n=g.size();
        int k=1;
        while((1<<k)<n) k++;
        par=VVI(k,VI(n,-1)),dep=VI(n),dat=vector<vector<Type>>(k,vector<Type>(n,Monoid::id()));
        dfs(g,root,-1);
        REP(i,k-1) REP(j,n) {
            par[i+1][j]=par[i][j]==-1?-1:par[i][par[i][j]];
            dat[i+1][j]=par[i][j]==-1?Monoid::id():Monoid::op(dat[i][j],dat[i][par[i][j]]);
        }
    }

    /// @brief パス u-v のモノイド積を返す
    Type fold(int u, int v) {
        if(dep[u]>dep[v]) swap(u,v);
        Type ret=Monoid::id();
        while(dep[u]<dep[v]) {
            int k=0;
            while((dep[v]-dep[u])>=(1<<(k+1))) k++;
            ret=Monoid::op(ret,dat[k][v]),v=par[k][v];
        }
        while(u!=v) {
            int k=0;
            while(par[k+1][u]!=par[k+1][v]) k++;
            ret=Monoid::op(ret,dat[k][u]),ret=Monoid::op(ret,dat[k][v]);
            u=par[k][u],v=par[k][v];
        }
        return ret;
    }

private:
    VVI par;
    VI dep;
    vector<vector<Type>> dat;
    void dfs(const vector<vector<pair<int,Type>>>& g, int now, int pre) {
        par[0][now]=pre; dep[now]=(pre==-1 ? 0 : dep[pre]+1);
        for(auto [nxt,cost]: g[now]) {
            if(nxt==pre) continue;
            dat[0][nxt]=cost;
            dfs(g,nxt,now);
        }
    }
};

#include"../../../kyopro_library/others/monoid.hpp"