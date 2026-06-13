#pragma once
#include "../../kyopro_library/template.hpp"

template<bool MIN>
struct RMQ {
    int N;
    vector<ll> dat;
    ll inf=(MIN? INFL: -INFL);

    RMQ(int N): N(N), dat(N<<1,inf) {}

    void set(int i, ll x) {
        i+=N;
        dat[i]=x;
        while(i>>=1) {
            dat[i]=MIN?
                min(dat[i<<1],dat[i<<1|1]):
                max(dat[i<<1],dat[i<<1|1]);
        }
    }

    ll query(int l, int r) {
        l+=N; r+=N;
        ll ret=inf;
        while(l<r) {
            if(l&1) MIN? chmin(ret,dat[l++]): chmax(ret,dat[l++]);
            if(r&1) MIN? chmin(ret,dat[--r]): chmax(ret,dat[--r]);
            l>>=1; r>>=1;
        }
        return ret;
    }
};
