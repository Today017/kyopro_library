#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/algorithm/binary_search.hpp"

/// @brief n　の k 乗根の切り捨てを返す
ll KthRoot(ll n, ll k=2) {
    if(k==1) return n;
    return (ll)BinarySearch<ll>(0,4e10,[&](ll x) {
        lll tmp=1;
        REP(i,k) {
            if(tmp*x>n) return false;
            tmp*=x;
        }
        return true;
    });
}