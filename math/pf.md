[top](../README.md)

# [Prime Factorize](./pf.cpp)

`vector<pair<ll, int>> prime_factorize(ll n)`
- 数 $n$ に対して、素因数分解を行う。
- $O(\sqrt{n})$

---

```cpp
vector<pair<ll, int>> prime_factorize(ll n) {
    vector<pair<ll, int>> ret;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0) {
            continue;
        }
        int ex = 0;
        while (n % i == 0) {
            ex++;
            n /= i;
        }
        ret.push_back(make_pair(i, ex));
    }
    if (n != 1) {
        ret.push_back(make_pair(n, 1));
    }
    return ret;
}

```