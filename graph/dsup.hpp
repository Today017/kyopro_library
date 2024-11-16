#include "../../kyopro_library/template.hpp"

template <typename Group, auto op, auto e, auto inv>
struct DsuPotentialized {
    DsuPotentialized() = default;
    DsuPotentialized(int n) {
        par = vector<int>(n);
        sz = vector<int>(n);
        diff_weight = vector<Group>(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
            diff_weight[i] = e();
        }
    }
    int find(int x) {
        if (par[x] == x) return x;
        int root = find(par[x]);
        diff_weight[x] = op(diff_weight[x], diff_weight[par[x]]);
        return par[x] = root;
    }
    bool merge(int x, int y, Group w) {
        w = op(w, diff_weight[x]);
        w = op(inv(diff_weight[y]), w);
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) {
            swap(x, y);
            w = inv(w);
        }
        par[y] = x;
        sz[x] += sz[y];
        diff_weight[y] = w;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
    Group diff(int x, int y) { return op(diff_weight[y], inv(diff_weight[x])); }
    int size(int x) { return sz[find(x)]; }

private:
    vector<int> par, sz;
    vector<Group> diff_weight;
};
