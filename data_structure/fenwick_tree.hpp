#pragma once
#include "../../kyopro_library/template.hpp"

struct FenwickTree {
    FenwickTree()=default;
    FenwickTree(int n) {
        this->n=n;
        dat=vector<ll>(n,0);
    }
    void add(int i, ll x) {
        i++;
        while(i<=n) dat[i-1]+=x, i+=i&-i;
    }
    ll sum(int l, int r) { return sum(r)-sum(l); }
    ll operator[](int i) { return sum(i,i+1); }
    int size() { return n; }

private:
    int n;
    vector<ll> dat;
    ll sum(int r) {
        ll ret=0;
        while(r>0) ret+=dat[r-1], r-=r&-r;
        return ret;
    }
};
