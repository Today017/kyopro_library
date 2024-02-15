[top](../README.md)

# [Rolling Hash](./rh.cpp)

`rolling_hash(string s, vector<ll> base)`
- 文字列 $s$ から $base$ を基数とした Rolling Hash を構築する。
- `base` に引数を渡さない場合、ランダムに選択される。複数の文字列の $Rolling Hash$ を別々に構築して後で比較を行う場合は、 `base` を揃えるように注意すること。
- $O(n)$

`hash get(int l, int r)`
- 区間 $[l, r)$ のハッシュ値を返す。
- $O(1)$

`hash connect(hash h1, hash h2, int len1)`
- 長さが $len_1$, ハッシュ値が $h1$ であるような文字列と、ハッシュ値が $h2$ であるような文字列を連結した文字列のハッシュ値を返す。
- $O(1)$

---

```cpp
struct rolling_hash {
    inline long long mul_mod(long long a, long long b, long long mod) {
        return a * b % mod;
    }
    inline long long add_mod(long long a, long long b, long long mod) {
        long long ret = a + b;
        if (ret >= mod) ret -= mod;
        if (ret < 0) ret += mod;
        return ret;
    }
    long long pow_mod(long long a, long long x, long long mod) {
        long long ret = 1;
        while (x) {
            if (x & 1) ret = mul_mod(ret, a, mod);
            a = mul_mod(a, a, mod);
            x >>= 1;
        }
        return ret;
    }
    vector<long long> mod = {998244353, 1000000007, 1000000009, 1000000021, 1000000033};
    vector<long long> base;
    vector<vector<long long>> power, hash_table, inv;
    rolling_hash(const string &s, vector<long long> base = {}) {
        int n = s.size();
        mt19937 rng(time(0));
        this->base = vector<long long>(5);
        power = vector<vector<long long>>(5);
        hash_table = vector<vector<long long>>(5);
        inv = vector<vector<long long>>(5);
        if (base.size() != 5) {
            for (int i = 0; i < 5; i++) this->base[i] = (rng() % mod[i] + 3000) % mod[i];
        } else {
            this->base = base;
        }
        base = this->base;
        for (int i = 0; i < 5; i++) {
            power[i] = vector<long long>(n + 1);
            hash_table[i] = vector<long long>(n + 1);
            inv[i] = vector<long long>(n + 1);
            power[i][0] = 1;
            inv[i][n] = pow_mod(pow_mod(base[i], n, mod[i]), mod[i] - 2, mod[i]);
        }
        for (int i = 0; i < n; i++) {
            int num = s[i] - 'A';
            for (int j = 0; j < 5; j++) {
                power[j][i + 1] = mul_mod(power[j][i], base[j], mod[j]);
                hash_table[j][i + 1] = add_mod(hash_table[j][i], mul_mod(power[j][i], num, mod[j]), mod[j]);
                inv[j][n - i - 1] = mul_mod(inv[j][n - i], base[j], mod[j]);
            }
        }
    }
    using hash = array<long long, 5>;
    hash get(int l, int r) {
        hash ret;
        for (int i = 0; i < 5; i++) {
            ret[i] = mul_mod(add_mod(hash_table[i][r], -hash_table[i][l], mod[i]), inv[i][l], mod[i]);
        }
        return ret;
    }
    hash connect(hash h1, hash h2, int len1) {
        hash ret;
        for (int i = 0; i < 5; i++) {
            ret[i] = add_mod(h1[i], mul_mod(h2[i], power[i][len1], mod[i]), mod[i]);
        }
        return ret;
    }
};
```