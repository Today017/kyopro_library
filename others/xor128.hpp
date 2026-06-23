#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief 疑似乱数生成

u64 Xor128() {
    static bool flag = false;
    static u64 x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    if(!flag) {
        random_device seedgen;
        w = seedgen();
        flag = true;
    }
    u64 t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

i64 Xor128(i64 n) { return Xor128() % n; }

i64 Xor128(i64 l, i64 r) { return Xor128(r - l) + l; }  //[l,r)

f80 Xor128Prob() { return (f80)Xor128() / (ULLONG_MAX); }
