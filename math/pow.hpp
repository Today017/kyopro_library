#pragma once
#include"../../kyopro_library/template.hpp"

///@brief モノイドの繰返し2乗法
///@note O(F log(K))
template<typename Monoid>
typename Monoid::Type MonoidPow(
    typename Monoid::Type X,
    ll K
) {
    using Type=typename Monoid::Type;
    Type ret=Monoid::id();
    while(K) {
        if(K&1) ret=Monoid::op(ret,X);
        X=Monoid::op(X,X);
        K>>=1;
    }
    return ret;
}
