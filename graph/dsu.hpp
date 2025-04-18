#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief Disjoint Set Union
struct DSU{
    DSU()=default;

    /// @brief コンストラクタ
    DSU(int n){
        par=VI(n); iota(ALL(par),0);
        sz=VI(n,1);
        forest_count=n;
    }

    /// @brief 頂点 x を含む連結成分の代表元を返す
    /// @note O(α(N))
    int find(int x){
        if(par[x]==x) return x;
        return par[x]=find(par[x]);
    }

    /// @brief 頂点 x と y を連結し、true を返す
    /// @brief 既に連結されている場合は false を返す
    /// @note O(α(N))
    bool merge(int x, int y){
        x=find(x); y=find(y);
        if(x==y) return false;
        if(sz[x]<sz[y]) swap(x,y);
        par[y]=x; sz[x]+=sz[y];
        forest_count--;
        return true;
    }

    /// @brief 頂点 x を含む連結成分のサイズを返す
    /// @note O(α(N))
    int size(int x){ return sz[find(x)]; }

    /// @brief 頂点 x と y が同じ連結成分に属するか否かを返す
    /// @note O(α(N))
    bool same(int x, int y){ return find(x)==find(y); }

    /// @brief 連結成分の個数を返す
    /// @note O(1)
    int count(){ return forest_count; }

    /// @brief 各頂点を連結成分に分解する
    /// @note O(N)
    VVI groups(){
        int n=par.size();
        VVI ret(n);
        REP(i,n) ret[find(i)].push_back(i);
        ret.erase(remove_if(ALL(ret),[&](const VI& v){ return v.empty(); }),ret.end());
        return ret;
    }

private:
    VI par,sz;
    int forest_count;
};


