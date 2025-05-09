#include"../../kyopro_library/template.hpp"

/// @brief 離散対数問題
/// @brief x^k=y mod m なる最小の k を返す
/// @note O(sqrt(m))
/// @attention p は素数
ll ModLog(ll x, ll y, ll mod) {
    ll m=ceil(sqrt(mod))+1;
    ll now_y=y;
    map<ll,ll> mp;
    REP(i,m) {
        mp[now_y]=i;
        now_y=now_y*x%mod;
    }
    ll x_pow=1;
    REP(i,m) {
        x_pow*=x;
        x_pow%=mod;
    }
    ll now_x=x_pow;
    FOR(i,1,m+1) {
        if(mp.find(now_x)!=mp.end()) return i*m-mp[now_x];
        now_x=now_x*x_pow%mod;
    }
    return -1;
}