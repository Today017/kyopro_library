[top](../README.md)

# [Z Algorithm](./zalgo.cpp)

`vector<int> z_algorithm(string s)`
- 文字列 $s(|s|=n)$ に対して、 $ret_i=$ 「 $S[0,n)$ と $S[i,n)$ の Longest Common Prefix の長さ」であるような配列 $ret$ を返す。
- $O(N)$

---

```cpp
vector<int> z_algorithm(const string &s) {
    int n = s.size();
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && s[j] == s[i + j]) {
            j++;
        }
        ret[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < n && k + ret[k] < j) {
            ret[i + k] = ret[k], ++k;
        }
        i += k;
        j -= k;
    }
    return ret;
}
```