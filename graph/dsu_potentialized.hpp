#include "../../kyopro_library/template.hpp"

/// @brief ポテンシャル付き DSU
/// @tparam Group 群
template<typename Group>
struct DsuPotentialized{
    using Type=typename Group::Type;
    DsuPotentialized()=default;

    /// @brief コンストラクタ
    DsuPotentialized(int n){
        par=VI(n); iota(ALL(par),0);
        sz=VI(n,1);
        diff_weight=vector<Type>(n,Group::id());
        forest_count=n;
    }

    /// @brief 頂点 x を含む連結成分の代表元を返す
    int find(int x){
        if(par[x]==x) return x;
        int root=find(par[x]);
        diff_weight[x]=Group::op(diff_weight[x],diff_weight[par[x]]);
        return par[x]=root;
    }

    /// @brief 頂点　x と y を連結し、weight(x) = op(weight(y), w) とする
    bool merge(int x, int y, Type w){
        w=Group::op(Group::inv(weight(y)),Group::op(w,weight(x)));
        x=find(x); y=find(y);
        if(x==y) return false;
        if(sz[x]<sz[y]){
            swap(x,y);
            w=Group::inv(w);
        }
        par[y]=x; sz[x]+=sz[y]; diff_weight[y]=w;
        forest_count--;
        return true;
    }

    /// @brief 頂点 x のポテンシャルを返す
    Type weight(int x){
        find(x);
        return diff_weight[x];
    }

    /// @brief op(inv(weight(y)), weight(x)) (x と y の間のポテンシャル差)を返す
    Type diff(int x, int y){ return Group::op(diff_weight[y],Group::inv(diff_weight[x])); }

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
    vector<Type> diff_weight;
    int forest_count;
};