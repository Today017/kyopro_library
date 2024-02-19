#include "../../kyopro_library/data_structure/fen.cpp"

long long inversion_number(const vector<int> &a) {
    int n = a.size();
    fenwick_tree<int> ft(n);
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += i - ft.sum(0, a[i]);
        ft.add(a[i], 1);
    }
    return ret;
}
