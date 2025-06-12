#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"
#include"../../kyopro_library/math/prime_factorize.hpp"
#include"../../kyopro_library/others/xor128.hpp"

/// @brief n の原始根を求める
/// @ref https://37zigen.com/primitive-root/
/// @ref verify: https://judge.yosupo.jp/problem/primitive_root
ll PrimitiveRoot(ll n) {
    if(!PrimalityTest(n)) return -1;
    if(n==2) return 1;

    auto pf=PrimeFactorize(n-1);
    while(true) {
        ll i=Xor128(2,n);
        bool ok=true;
        for(auto [p,_]: pf) {
            if(ModPow(i,(n-1)/p,n)==1) {
                ok=false;
                break;
            }
        }
        if(ok) return i;
    }
    return-1;
}