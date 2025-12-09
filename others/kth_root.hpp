#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/algorithm/binary_search.hpp"

/// @brief n　の k 乗根の切り捨てを返す
ll KthRoot(ll n, ll k=2) {
    if(k==1) return n;
    return (ll)BinarySearch<ll>(0,4e10,[&](ll x) {
        __int128_t tmp=1;
        for(int i=0; i<k; i++) {
            if(tmp*x>n) return false;
            tmp*=x;
        }
        return true;
    });
}