#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/algorithm/binary_search.hpp"

/// @brief n　の k 乗根の切り捨てを返す
ll KthRoot(ll n, ll k=2) {
    if(k==1) return n;
    return (ll)BinarySearch<LL>(0,4e10,[&](LL x) {
        LL tmp=1;
        bool flag=true;
        REP(i,k) {
            if(tmp*x>n) return false;
            tmp*=x;
        }
        return true;
    });
}