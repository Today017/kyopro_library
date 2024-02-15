[top](../README.md)

# [Generate Primes](./name.cpp)

`vector<int> generate_primes(int n)`
- エラトステネスの篩により、 $n$ 以下の素数を列挙する。
- $O(n\log{\log{n}})$

---

```cpp
vector<int> generate_primes(int n) {
    vector<int> ret;
    vector<bool> vst(n + 1, false);
    vst[0] = vst[1] = true;
    for (int i = 2; i <= n; i++) {
        if (vst[i]) continue;
        ret.push_back(i);
        for (int j = 2 * i; j <= n; j += i) vst[j] = true;
    }
    return ret;
}
```