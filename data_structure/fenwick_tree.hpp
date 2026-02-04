#pragma once
#include "../../kyopro_library/template.hpp"

///@brief フェニック木
struct FenwickTree {
    FenwickTree()=default;
    FenwickTree(int n): dat(n) {}
    void add(int i, ll x) {
        i++;
        while(i<=dat.size()) dat[i-1]+=x, i+=i&-i;
    }
    ll sum(int l, int r) { return sum(r)-sum(l); }
    ll operator[](int i) { return sum(i,i+1); }
    int size() { return dat.size(); }

private:
    vector<ll> dat;
    ll sum(int r) {
        ll ret=0;
        while(r>0) ret+=dat[r-1], r-=r&-r;
        return ret;
    }
};
