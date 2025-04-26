#include"../../kyopro_library/template.hpp"

/// @brief オイラーのtotient関数を前計算する
/// @brief totient(0) ... totient(n) を前計算する
/// @note O(n log(log(n)))
/// @ref https://qiita.com/drken/items/3beb679e54266f20ab63
/// @ref https://manabitimes.jp/math/667
/// @brief totient(i) = i 以下であって、i と互いに素な数の個数
/// @brief 公式: totient(n) = n * Π(1 - 1/p) (p は n の素因数)
/// @brief 公式: totient(n)totient(m) = totient(nm) (n と m が互いに素)
/// @brief 公式: Σ(d | n) totient(d) = n
/// @brief 公式: a^totient(m) ≡ 1 (mod m) (a と m が互いに素)
VL TotientTable(ll n) {
    VL ret(n+1); iota(ALL(ret),0);

    FOR(i,2,n+1) if(ret[i]==i) for(ll j=i; j<=n; j+=i) ret[j]=ret[j]/i*(i-1);

    return ret;
}