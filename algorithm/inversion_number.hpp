#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/data_structure/fen.hpp"

ll inversionNumber(const vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        assert(0 <= a[i] && a[i] < n);
    }
    FenwickTree<int> ft(n);
    ll ret = 0;
    for (int i = 0; i < n; i++) {
        ret += i - ft.sum(0, a[i]);
        ft.add(a[i], 1);
    }
    return ret;
}
