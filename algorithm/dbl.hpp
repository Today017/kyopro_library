#include "../../kyopro_library/template.hpp"

template <int Log>
struct Doubling {
    Doubling(const vector<int>& a) {
        int n = a.size();
        dat = vector<vector<int>>(Log + 1, vector<int>(n));
        for (int i = 0; i < n; i++) dat[0][i] = a[i];
        for (int i = 0; i < Log; i++) {
            for (int j = 0; j < n; j++) dat[i + 1][j] = dat[i][dat[i][j]];
        }
    }
    int transition(int start, ll k) {
        for (int b = 0; k > 0; b++, k >>= 1) {
            if (k & 1) start = dat[b][start];
        }
        return start;
    }

private:
    vector<vector<int>> dat;
};
