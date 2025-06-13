#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/others/modcal.hpp"
#include"../../kyopro_library/math/ntt.hpp"

/// @brief x=ai mod mi を満たす x mod m を返す
ll Garner(vector<ll> a, vector<ll> m, ll mod=INFL+3) {
    m.push_back(mod);
    int n=a.size();
    vector<ll> kp(n+1), rm(n+1,1ll);
    for(int i=0; i<n; i++) {
        ll x=((a[i]-kp[i]+m[i])%m[i])*ModInv(rm[i],m[i]);
        x%=m[i];
        for(int j=i+1; j<=n; j++) {
            (kp[j]+=rm[j]*x)%=m[j];
            (rm[j]*=m[i])%=m[j];
        }
    }
    return kp[n];
}

/// @brief a, b の自然数での畳み込みを返す
/// @tparam USE 使う素数の個数
/// @brief `USE=1` 最終的な配列の値が `X < 1224736769 = 1.2*10^9 = 2^30`
/// @brief `USE=2` 最終的な配列の値が `X < 575334854091079681 = 5.8*10^17 = 2^59`
/// @brief `USE=3` 最終的な配列の値が `X < 2^86`
template<int USE>
vector<ll> ConvolveInt64(vector<ll> a, vector<ll> b, ll mod=INFL+3) {
    constexpr const ll MOD1=1224736769, P1=3;
    constexpr const ll MOD2=469762049, P2=3;
    constexpr const ll MOD3=167772161, P3=3;
    static NTT<MOD1,P1> ntt1; static NTT<MOD2,P2> ntt2; static NTT<MOD3,P3> ntt3;

    if(USE==1) {
        auto c=ntt1.convolve(a,b);
        vector<ll> ret(c.size());
        for(int i=0; i<ret.size(); i++) ret[i]=c[i]%mod;
        return ret;
    }

    if(USE==2) {
        auto c1=ntt1.convolve(a,b);
        auto c2=ntt2.convolve(a,b);

        vector<ll> ret(c1.size());
        for(int i=0; i<ret.size(); i++) ret[i]=Garner({c1[i],c2[i]}, {MOD1,MOD2}, mod);
        return ret;
    }

    auto c1=ntt1.convolve(a,b);
    auto c2=ntt2.convolve(a,b);
    auto c3=ntt3.convolve(a,b);

    vector<ll> ret(c1.size());
    for(int i=0; i<ret.size(); i++) ret[i]=Garner({c1[i],c2[i],c3[i]}, {MOD1,MOD2,MOD3}, mod);
    return ret;
}