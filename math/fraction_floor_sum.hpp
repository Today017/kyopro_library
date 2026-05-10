#include"../../kyopro_library/others/kth_root.hpp"

ll FractionFloorSum(ll N) {
    ll r=KthRoot(N,2);

    ll ret=0;
    for(ll i=1; i<=r; i++) ret+=((N/i)-(N/(i+1)))*i;
    for(ll i=1; i<=N/(r+1); i++) ret+=N/i;

    return ret;
}
