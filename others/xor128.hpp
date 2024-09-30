#include "../../kyopro_library/template.hpp"

struct Random {
    Random(uint64_t seed = time(0)) {
        x = 123456789;
        y = 362436069;
        z = 521288629;
        w = 88675123;
        x ^= seed;
        y ^= (seed << 8);
        z ^= (seed << 16);
        w ^= (seed << 24);
    }
    inline uint64_t operator()(uint64_t n = INFL) {
        uint64_t t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        uint64_t ret = (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
        return ret % n;
    }
    inline uint64_t operator()(uint64_t l, uint64_t r) { return operator()(r - l) + l; }
    inline double prob() { return (double)operator()(1LL << 32) / (1LL << 32); }

private:
    uint64_t x, y, z, w;
};