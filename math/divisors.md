[top](../README.md)

# [Divisors](./divisors.cpp)

`vector<ll> divisors(ll n)`
- 自然数 $n$ の約数を列挙する。
- $O(\sqrt{n})$

---

```cpp
vector<ll> divisors(ll n) {
    vector<ll> ret;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i != 0) {
            continue;
        }
        ret.push_back(i);
        if (n / i != i) {
            ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
```