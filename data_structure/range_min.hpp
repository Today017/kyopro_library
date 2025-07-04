#include"../../kyopro_library/template.hpp"

struct RangeMin {
    int n;
    vector<ll> dat;
    RangeMin(int m) { n=m; dat=vector<ll>(2*n,INF); }
    void set(int i, ll x) {
        dat[i+=n]=x;
        while(i>>=1) dat[i]=min(dat[i<<1],dat[i<<1|1]);
    }
    ll get(int l, int r) {
        l+=n; r+=n;
        ll ret=INF;
        while(l<r) {
            if(l&1) chmin(ret,dat[l++]);
            if(r&1) chmin(ret,dat[--r]);
            l>>=1; r>>=1;
        }
        return ret;
    }
};
