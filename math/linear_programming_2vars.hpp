#include"../../kyopro_library/template.hpp"

/// @brief 2変数の線形計画問題
/// @brief ax + by >= c, x >= 0, y >= 0 という条件のもと、px+qy の最小値を返す
/// @note O(sqrt(c))
ll LinearProgramming_2valiables(ll a, ll b, ll c, ll p, ll q) {
    if(a*q<b*p) swap(a,b), swap(p,q);
    ll ret=INFL;
    if(a*a>c) {
        for(ll x=0; x<=(c+a-1)/a; x++) {
            ll y=max(0LL,(c-a*x+b-1)/b);
            ret=min(ret,p*x+q*y);
        }
    }else{
        for(ll y=0; y<a&&y<=(c+b-1)/b; y++) {
            ll x=max(0LL,(c-b*y+a-1)/a);
            ret=min(ret,p*x+q*y);
        }
    }
    return ret;
}