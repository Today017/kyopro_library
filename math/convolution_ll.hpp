#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/ntt.hpp"

/// @brief x=ai mod mi を満たす x mod m を返す
ll Garner(ll a1, ll a2, ll a3, ll m1, ll m2, ll m3, ll mod=INFL+3){
    const ll a[]={a1,a2,a3}, m[]={m1,m2,m3,mod};
    vector<ll> kp(4), rm(4,1ll);
    REP(i,3){
        ll x=((a[i]-kp[i]+m[i])%m[i])*ModInv(rm[i],m[i]);
        x%=m[i];
        FOR(j,i+1,4){
            (kp[j]+=rm[j]*x)%=m[j];
            (rm[j]*=m[i])%=m[j];
        }
    }

    return kp[3];
}

// /// @brief a, b の自然数での畳み込みを返す
// VL ConvolveInt64(VL a, VL b, ll mod=INFL+3){
//     constexpr const ll MOD1=167772161,P1=3;
//     constexpr const ll MOD2=469762049,P2=3;
//     constexpr const ll MOD3=754974721,P3=11;
//     static NTT<MOD1,P1> ntt1;
//     static NTT<MOD2,P2> ntt2;
//     static NTT<MOD3,P3> ntt3;

//     auto c1=ntt1.convolve(a,b);
//     auto c2=ntt2.convolve(a,b);
//     auto c3=ntt3.convolve(a,b);

//     VL ret(c1.size());
//     REP(i,ret.size()) ret[i]=Garner(c1[i],c2[i],c3[i],MOD1,MOD2,MOD3,mod);

//     return ret;
// }

#include<atcoder/convolution>

/// @brief a, b の自然数での畳み込みを返す
VL ConvolveInt64(VL a, VL b, ll mod=INFL+3){
    constexpr const ll MOD1=167772161,P1=3;
    constexpr const ll MOD2=469762049,P2=3;
    constexpr const ll MOD3=754974721,P3=11;

    auto c1=atcoder::convolution<MOD1>(a,b);
    auto c2=atcoder::convolution<MOD1>(a,b);
    auto c3=atcoder::convolution<MOD1>(a,b);

    VL ret(c1.size());
    REP(i,ret.size()) ret[i]=Garner(c1[i],c2[i],c3[i],MOD1,MOD2,MOD3,mod);

    return ret;
}