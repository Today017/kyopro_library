#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/math/fps.hpp"

template <typename T>
vector<T> multipointEvaluate(vector<T> f, vector<T> x) {
    int n = x.size();
    if (n == 0) return {};
    if (n == 1) {
        T ret = 0, tmp = 1;
        for (T a : f) ret += a * tmp, tmp *= x[0];
        return {ret};
    }
    int n2 = 1;
    while (n2 < n) n2 <<= 1;
    vector<vector<T>> g(n2 * 2, {1});
    for (int i = 0; i < n; i++) g[n2 + i] = {-x[i], 1};
    for (int i = n2 - 1; i > 0; i--) g[i] = polyMul(g[i << 1 | 0], g[i << 1 | 1]);

    g[1] = polyDiv(f, g[1]).second;
    for (int i = 2; i < n2 + n; i++) g[i] = polyDiv(g[i >> 1], g[i]).second;
    vector<T> ret(n);
    for (int i = 0; i < n; i++) ret[i] = g[n2 + i][0];
    return ret;
}