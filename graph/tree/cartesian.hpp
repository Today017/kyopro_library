#pragma once
#include "../../../kyopro_library/template.hpp"

/// @brief Cartesian Tree（デカルト木）
vi Cartesian(vi P) {
    ll N = P.size();
    vi ret(N, -1), stk;
    rep(i, N) {
        int prv = -1;
        while(!stk.empty() && P[i] < P[stk.back()]) {
            prv = stk.back();
            stk.pop_back();
        }
        if(prv != -1) ret[prv] = i;
        if(!stk.empty()) ret[i] = stk.back();
        stk.push_back(i);
    }
    return ret;
}