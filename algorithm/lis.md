[top](../README.md)

# [Longest Increasing Subsequence](./lis.cpp)

`int longest_increasing_subsequence_length(vector<int> a, bool strict = true)`
- 数列 $a$ の最長増加部分列の長さを返す。
- `strict` が `false` の場合、狭義単調増加列について数える。
- $O(n\log{n})$

---

```cpp
int longest_increasing_subsequence_length(vector<int> &a, bool strict = true) {
    int n = a.size();
    vector<int> dp(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        vector<int>::iterator itr;
        if (strict) {
            itr = lower_bound(dp.begin(), dp.end(), a[i]);
        } else {
            itr = upper_bound(dp.begin(), dp.end(), a[i]);
        }
        *itr = a[i];
    }
    return find(dp.begin(), dp.end(), INT_MAX) - dp.begin();
}

```