#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/modcal.hpp"

struct CombinationLucas {
    vector<ll> fact, factinv;
    int mod;
    CombinationLucas(int mod) {
        this->mod = mod;
        fact = vector<ll>(mod);
        factinv = vector<ll>(mod);
        fact[0] = 1;
        for (int i = 1; i < mod; i++) fact[i] = fact[i - 1] * i % mod;
        factinv[mod - 1] = modInv(fact[mod - 1], mod);
        for (int i = mod - 2; i >= 0; i--) factinv[i] = factinv[i + 1] * (i + 1) % mod;
    }
    ll calc(int n, int r) {
        if (n < r || r < 0 || n < 0) return 0;
        return fact[n] * factinv[r] % mod * factinv[n - r] % mod;
    }
    ll nCr(int n, int r) {
        if (r == 0 || r == n) return 1;
        return calc(n % mod, r % mod) * nCr(n / mod, r / mod) % mod;
    }
};