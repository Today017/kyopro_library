#include "../../kyopro_library/template.hpp"

///@brief 転倒数
///@brief 配列 v の転倒数を求める
///@note O(N log(N))時間 / O(N log(N))空間
ll InversionNumber(const vector<int>& v) {
    //座圧する必要がない代わりに空間がΘ(N log(N)) どっちがいいんだろうね
    ll ret=0;
    auto Merge=[&](const vector<int>& a, const vector<int>& b) {
        int n=a.size();
        int r=0;
        rep(l,n) {
            while(r<n && b[r]<a[l]) r++;
            ret+=r;
        }
        vector<int> c(2*n);
        merge(all(a),all(b),c.begin());
        return c;
    };

    int n=v.size(),n2=1;
    while(n2<n) n2<<=1;
    vector<vector<int>> node(n2<<1,vector<int>(1,INF));
    rep(i,n) node[i+n2].pop_back();
    for(int i=n2; i>0; i--) node[i]=Merge(node[i<<1],node[i<<1|1]); 
    return ret;
}

#include "../../kyopro_library/data_structure/fenwick_tree.hpp"

///@brief 転倒数（座圧するバージョン）
///@brief 配列 v の転倒数を求める
///@note 座圧が必要
ll InversionNumber2(const vector<int>& v) {
    int n=v.size();
    auto a=v;
    sort(all(a)); a.erase(unique(all(a)),a.end());
    int m=a.size();
    FenwickTree fen(m);
    ll ret=0;
    rep(i,n) {
        int x=lower_bound(all(a),v[i])-a.begin();
        ret+=fen.sum(x+1,m);
        fen.add(x,1);
    }
    return ret;
}
