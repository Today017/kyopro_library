#include "../../kyopro_library/template.hpp"

template<typename T>
T pow_mod(T a, T n, T mod) {
    T ret = 1;
    while (n > 0) {
        if (n & 1) {
            ret = ret * a % mod;
        }
        a = a * a % mod;
        n >>= 1;
    }
    return ret;
}

bool miller_rabin(ll N, vector<ll> A) {
    if (N == 2) {
        return true;
    }
    if (N == 1 || N % 2 == 0) {
        return false;
    }

    ll d = N - 1;
    ll s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    for (ll a : A) {
        if (a >= N) {
            break;
        }
        ll x = pow_mod<__int128_t>(a, d, N);
        if (x == 1 || x == N - 1) {
            continue;
        }
        bool ok = false;
        for (ll i = 0; i < s - 1; i++) {
            x = __int128_t(x) * x % N;
            if (x == N - 1) {
                ok = true;
                break;
            }
        }
        if (!ok) {
            return false;
        }
    }
    return true;
}

bool primaliry_test(ll n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    if (n < 4759123141LL) {
        return miller_rabin(n, {2, 7, 61});
    } else {
        return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    }
}
