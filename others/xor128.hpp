#pragma once
#include "../../kyopro_library/template.hpp"

uint64_t xor128() {
    static bool flag = false;
    static uint64_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    if (!flag) {
        w = time(0);
        flag = true;
    }
    uint64_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
uint64_t xor128(uint64_t n) { return xor128() % n; }
uint64_t xor128(uint64_t l, uint64_t r) { return xor128(r - l) + l; } // [l, r)
double xor128_prob() { return (double)xor128() / (1LL << 32); }