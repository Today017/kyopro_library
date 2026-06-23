#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief Disjoint Set Union
struct DSU {
    DSU() = default;

    DSU(int n) {
        par = vi(n);
        iota(all(par), 0);
        sz = vi(n, 1);
        forest_count = n;
    }

    int find(int x) {
        if(par[x] == x) return x;
        return par[x] = find(par[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        if(sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        forest_count--;
        return true;
    }

    int size(int x) { return sz[find(x)]; }

    bool same(int x, int y) { return find(x) == find(y); }

    int count() { return forest_count; }

    vector<vi> groups() {
        int n = par.size();
        vector<vi> ret(n);
        rep(i, n) ret[find(i)].push_back(i);
        ret.erase(remove_if(all(ret), [&](const vi& v) { return v.empty(); }), ret.end());
        return ret;
    }

private:
    vi par, sz;
    int forest_count;
};
