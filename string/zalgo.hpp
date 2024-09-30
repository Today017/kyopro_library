#include "../../kyopro_library/template.hpp"

template <typename T = string>
vector<int> zAlgorithm(const T &s) {
    int n = s.size();
    vector<int> A(n);
    for (int i = 0; i < n; ++i) A[i] = s[i];
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && A[j] == A[i + j]) j++;
        ret[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < n && k + ret[k] < j) ret[i + k] = ret[k], ++k;
        i += k;
        j -= k;
    }
    return ret;
}
