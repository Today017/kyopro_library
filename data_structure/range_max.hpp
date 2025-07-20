#include"../../kyopro_library/template.hpp"

struct RangeMax {
    int n;
    vector<ll> dat;
    RangeMax(int m) { n=m; dat=vector<ll>(2*n,-INFL); }
    void set(int i, ll x) {
        dat[i+=n]=x;
        while(i>>=1) dat[i]=max(dat[i<<1],dat[i<<1|1]);
    }
    ll get(int l, int r) {
        l+=n; r+=n;
        ll ret=-INFL;
        while(l<r) {
            if(l&1) chmax(ret,dat[l++]);
            if(r&1) chmax(ret,dat[--r]);
            l>>=1; r>>=1;
        }
        return ret;
    }
};
