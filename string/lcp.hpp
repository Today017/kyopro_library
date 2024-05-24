#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/string/sa.hpp"

template <typename T>
vector<int> lcp_array(const T &s) {
    vector<int> sa = suffix_array(s);
    int n = s.size();
    vector<int> inv(n);
    for (int i = 0; i < n; i++) {
        inv[sa[i]] = i;
    }
    vector<int> ret(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (inv[i] == 0) continue;
        int j = sa[inv[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        ret[inv[i] - 1] = h;
    }
    return ret;
}