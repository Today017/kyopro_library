#include "../../kyopro_library/template.hpp"

template <typename T>
vector<vector<T>> matMul(const vector<vector<T>>& a, const vector<vector<T>>& b) {
    int n = a.size();
    vector<vector<T>> ret(n, vector<T>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) ret[i][j] += a[i][k] * b[k][j];
        }
    }
    return ret;
}

template <typename T>
vector<vector<T>> matPow(vector<vector<T>> a, ll b) {
    int n = a.size();
    vector<vector<T>> ret(n, vector<T>(n));
    for (int i = 0; i < n; i++) ret[i][i] = 1;
    while (b) {
        if (b & 1) ret = matMul(ret, a);
        a = matMul(a, a);
        b >>= 1;
    }
    return ret;
}