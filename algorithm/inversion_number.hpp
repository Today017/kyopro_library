#include "../../kyopro_library/template.hpp"

/// @brief 転倒数
/// @brief 配列 v の転倒数を求める
/// @note O(N log(N))
ll InversionNumber(const VI& v) {
    ll ret=0;
    auto Merge=[&](const VI& a, const VI& b){
        int n=a.size();
        int r=0;
        REP(l,n){
            while(r<n&&b[r]<a[l]) r++;
            ret+=r;
        }
        VI c(2*n);
        merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());
        return c;
    };

    int n=v.size(),n2=1;
    while(n2<n) n2<<=1;
    vector<VI> node(n2<<1,VI(1,INF));
    REP(i,n) node[i+n2][0]=v[i];
    for(int i=n2-1; i>0; i--) node[i]=Merge(node[i<<1],node[i<<1|1]);
    return ret;
}