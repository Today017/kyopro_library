#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/algorithm/binary_search.hpp"

/// @brief n　の k 乗根の切り捨てを返す
template <typename T>
T KthRoot(T n, ii k = 2) {
    if(k == 1) return n;
    return (T)BinarySearch<T>(0, 4e10, [&](T x) {
        i128 tmp = 1;
        rep(i, k) {
            if(tmp * x > n) return false;
            tmp *= x;
        }
        return true;
    });
}