#pragma once
#include "../../kyopro_library/template.hpp"

struct DsuBaseSemigroup {
    using Type=ll;
    static Type op(Type a, Type b) { return a+b; }
};

///@brief 値をマージする DSU
///@tparam Semigroup 半群
///@attention コンテナを乗せる場合、値渡しで受け取るようにして、最後もreturn move(r)みたいにして返すこと
template<typename Semigroup=DsuBaseSemigroup>
struct DsuMerging {
    using Type=typename Semigroup::Type;
    DsuMerging()=default;

    ///@brief コンストラクタ
    DsuMerging(int n, const vector<Type>& v) {
        assert(n==v.size());
        par=vi(n); iota(all(par),0);
        sz=vi(n,1);
        dat=v;
        forest_count=n;
    }

    ///@brief 頂点 x を含む連結成分の代表元を返す
    ///@note O(α(N))
    int find(int x) {
        if(par[x]==x) return x;
        return par[x]=find(par[x]);
    }

    ///@brief 頂点 x と y を連結し、true を返す
    ///@brief 既に連結されている場合は false を返す
    ///@note O(α(N))
    bool merge(int x, int y) {
        x=find(x); y=find(y);
        if(x==y) return false;
        if(sz[x]>=sz[y]) {
            par[y]=x; sz[x]+=sz[y];
            //dat[x]=Semigroup::op(dat[x],dat[y]);
            //コピーコストがかかってしまう
            //std::moveで回避！
            dat[x]=Semigroup::op(move(dat[x]),move(dat[y]));
        } else {
            par[x]=y; sz[y]+=sz[x];
            //dat[y]=Semigroup::op(dat[x],dat[y]);
            dat[y]=Semigroup::op(move(dat[x]),move(dat[y]));
        }
        forest_count--;
        return true;
    }

    ///@brief 頂点 x を含む連結成分の半群積を返す
    Type& inspect(int x) { return dat[find(x)]; }

    Type get(int x) { return dat[find(x)]; }

    ///@brief 頂点 x を含む連結成分のサイズを返す
    int size(int x) const { return sz[find(x)]; }

    ///@brief 頂点 x と y が同じ連結成分に属するか否かを返す
    bool same(int x, int y) { return find(x)==find(y); }

    ///@brief 連結成分の個数を返す
    int count() const { return forest_count; }

    ///@brief 各頂点を連結成分に分解する
    vector<vi> groups() const {
        int n=par.size();
        vector<vi> ret(n);
        rep(i,n) ret[find(i)].push_back(i);
        ret.erase(remove_if(all(ret),[&](const vi& v) { return v.empty(); }),ret.end());
        return ret;
    }

private:
    vi par,sz;
    vector<Type> dat;
    int forest_count;
};
