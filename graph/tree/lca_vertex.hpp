#include "../../../kyopro_library/template.hpp"

/// @brief 頂点属性 LCA
/// @ref verify: https://onlinejudge.u-aizu.ac.jp/solutions/problem/3372/revector<int>ew/10572853/Today03/C++17
template<typename Monoid>
struct LcaVertex {
    using Type=typename Monoid::Type;

    /// @brief コンストラクタ
    /// @param v 頂点の重み
    LcaVertex(const vector<vector<int>>& g, const vector<Type>& v, int root=0) {
        int n=g.size();
        int k=1;
        while((1<<k)<n) k++;
        par=vector<vector<int>>(k,vector<int>(n,-1)),dep=vector<int>(n),dat=vector<vector<Type>>(k,vector<Type>(n,Monoid::id()));
        dfs(g,v,root,-1);
        for(int i=0; i<k-1; i++) for(int j=0; j<n; j++) {
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
            while(dep[v]-dep[u]>=(1<<(k+1))) k++;
            ret=Monoid::op(ret,dat[k][v]),v=par[k][v];
        }
        while(u!=v) {
            int k=0;
            while(par[k+1][u]!=par[k+1][v]) k++;
            ret=Monoid::op(ret,dat[k][u]),ret=Monoid::op(ret,dat[k][v]);
            u=par[k][u],v=par[k][v];
        }
        ret=Monoid::op(ret,dat[0][u]);
        return ret;
    }

private:
    vector<vector<int>> par;
    vector<int> dep;
    vector<vector<Type>> dat;
    void dfs(const vector<vector<int>>& g, const vector<Type>& v, int now, int pre) {
        dat[0][now]=v[now]; par[0][now]=pre; dep[now]=(pre==-1 ? 0 : dep[pre]+1);
        for(int nxt: g[now]) {
            if(nxt==pre) continue;
            dfs(g,v,nxt,now);
        }
    }
};

#include"../../../kyopro_library/others/monoid.hpp"