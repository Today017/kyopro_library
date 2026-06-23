#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief Z Algorithm
/// @brief `ret[i] = [0, n) と [i, n) の最長共通接頭辞の長さ`
template <typename T = string>
vi ZAlgorithm(const T& s) {
    int n = s.size();
    vi A(n);
    rep(i, n) A[i] = s[i];
    vi ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while(i < n) {
        while(i + j < n && A[j] == A[i + j]) j++;
        ret[i] = j;
        if(j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while(i + k < n && k + ret[k] < j) ret[i + k] = ret[k], ++k;
        i += k;
        j -= k;
    }
    return ret;
}