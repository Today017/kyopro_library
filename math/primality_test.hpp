#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"

/// @brief ミラーラビン素数判定法により n が素数であるかを判定する
/// @note O(k log^3 n)
/// @ref https://drken1215.hatenablog.com/entry/2023/05/23/233000
/// @ref verify: https://judge.yosupo.jp/problem/primality_test
bool PrimalityTest(ll n) {
    if(n==2) return true;
    if(n<=1||n%2==0) return false;

    VL test;
    if(n<4759123141ll) test={2,7,61};
    else test={2,325,9375,28178,450775,9780504,1795265022};

    ll s=0,d=n-1;
    while(d%2==0) d>>=1,s++;

    for(ll a:test) {
        if(a>=n) break;
        lll x=ModPow<lll>(a,d,n);

        if(x==1||x==n-1) continue;
        else {
            for(ll r=1; r<s; r++) {
                x=x*x%n;
                if(x==1) return false;
                else if(x==n-1) break;
            }
        }
        if(x!=n-1) return false;
    }

    return true;
}