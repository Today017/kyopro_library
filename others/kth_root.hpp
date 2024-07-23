#include "../../kyopro_library/template.hpp"

uint64_t kthRoot(uint64_t n, ll k = 2) {
    if (k == 1) {
        return n;
    }
    __uint128_t ok = 0, ng = 4e10;
    while (ng - ok > 1) {
        __uint128_t mid = (ok + ng) / 2;
        __uint128_t tmp = 1;
        bool flag = true;
        for (int i = 0; i < k; i++) {
            if (tmp * mid > n) {
                ng = mid;
                flag = false;
                break;
            }
            tmp *= mid;
        }
        if (flag) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}