[top](../README.md)

# Utils

[`ll modPow(ll a, ll n, ll p)`](./modcal.hpp)
- $a^n \mod p$ を返す。
- $O(\log n)$

[`ll modInv(ll a, ll p)`](./modcal.hpp)
- $a^{-1} \mod p$ を返す。
- $p$ は素数。
- $O(\log p)$

[`u64 kthRoot(u64 n, ll k = 2)`](./kth_root.hpp)
- $\lfloor \sqrt[k]{n} \rfloor$ を返す。
- $O(\log MAX(=10^{10}) \log k)$