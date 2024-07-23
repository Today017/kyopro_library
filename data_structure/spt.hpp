#include "../../kyopro_library/template.hpp"

template <typename T, bool Min = true>
struct SparseTable {
    SparseTable(const vector<T> &a) {
        n = a.size();
        log_table = vector<int>(n + 1);
        sign = Min ? 1 : -1;
        for (int i = 2; i <= n; i++) {
            log_table[i] = log_table[i >> 1] + 1;
        }
        dat = vector<vector<T>>(log_table[n] + 1, vector<T>(n));
        for (int i = 0; i < n; i++) {
            dat[0][i] = a[i] * sign;
        }
        for (int i = 1; (1 << i) <= n; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                dat[i][j] = min(dat[i - 1][j], dat[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    T query(int l, int r) {
        int k = log_table[r - l];
        return min(dat[k][l], dat[k][r - (1 << k)]) * sign;
    }

private:
    int n;
    vector<vector<T>> dat;
    vector<int> log_table;
    int sign;
};