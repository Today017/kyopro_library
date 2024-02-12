[top](../lib.md)

# [Divisors](./divisors.cpp)

`vector<long long> divisors(long long n)`
- 自然数 $n$ の約数を列挙する。
- $O(\sqrt{n})$

---

```cpp
vector<long long> divisors(long long n) {
    vector<long long> ret;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i != 0) continue;
        ret.push_back(i);
        if (n / i != i) ret.push_back(n / i);
    }
    sort(ret.begin(), ret.end());
    return ret;
}
```