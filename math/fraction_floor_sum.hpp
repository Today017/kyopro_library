#include"../../kyopro_library/others/kth_root.hpp"

ll FractionFloorSum(ll n) {
    ll r=KthRoot(n,2);

    ll ret=0;
    for(ll i=1; i<=r; i++) ret+=((n/i)-(n/(i+1)))*i;
    for(ll i=1; i<=n/(r+1); i++) ret+=n/i;

    return ret;
}
