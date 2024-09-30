#include "../../kyopro_library/template.hpp"

vector<ll> totientTable(ll n) {
    vector<ll> ret(n + 1);
    iota(ret.begin(), ret.end(), 0);
    for (ll i = 2; i <= n; i++) {
        if (ret[i] == i) {
            for (ll j = i; j <= n; j += i) ret[j] = ret[j] / i * (i - 1);
        }
    }
    return ret;
}
