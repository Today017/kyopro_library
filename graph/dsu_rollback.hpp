#include"../../kyopro_library/template.hpp"

/// @brief ロールバック可能DSU
struct DsuRollback{
    DsuRollback()=default;

    /// @brief コンストラクタ
    DsuRollback(int n){
        par=VI(n); iota(ALL(par),0);
        sz=VI(n,1);
        forest_count=n;
    }

    /// @brief 頂点 x を含む連結成分の代表元を返す
    int find(int x){
        if(par[x]==x) return x;
        return find(par[x]);
    }

    /// @brief 頂点 x と y を連結し、true を返す
    /// @brief 既に連結されている場合は false を返す
    bool merge(int x, int y){
        x=find(x); y=find(y);
        if(x==y){
            history.push_back({x,-1,-1,-1});
            return false;
        }
        if(sz[x]<sz[y]) swap(x,y);
        history.push_back({x,y,sz[x],sz[y]});
        par[y]=x; sz[x]+=sz[y];
        forest_count--;
        return true;
    }

    /// @brief 最後に行った連結操作を取り消す
    void undo(){
        if(history.empty()) return;
        auto[x,y,szx,szy]=history.back();
        history.pop_back();
        if(y==-1)return;
        par[y]=y; sz[x]=szx; sz[y]=szy;
    }

    /// @brief DSUの状態を上書き保存する
    void snapshot(){ history.clear(); }

    /// @brief 最後に snapshot した時点まで巻き戻す
    void rollback(){ while(!history.empty()) undo(); }

    /// @brief 頂点 x を含む連結成分のサイズを返す
    int size(int x){ return sz[find(x)]; }

    /// @brief 頂点 x と y が同じ連結成分に属するか否かを返す
    bool same(int x, int y){ return find(x)==find(y); }

    /// @brief 連結成分の個数を返す
    int count(){ return forest_count; }

    /// @brief 各頂点を連結成分に分解する
    VVI groups(){
        int n=par.size();
        VVI ret(n);
        REP(i,n) ret[find(i)].push_back(i);
        ret.erase(remove_if(ALL(ret),[&](const VI& v){ return v.empty(); }),ret.end());
        return ret;
    }

private:
    VI par,sz;
    vector<tuple<int,int,int,int>> history;
    int forest_count;
};
