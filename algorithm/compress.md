[top](../lib.md)

# [Compress](./compress.cpp)

`vector<T> compress(vector<T> a)`

- $a$ を座標圧縮する。
- $ret_{a_i}$ が $a_i$ の圧縮前の値であるような $ret$ を返す。
- $O(n\log{n})$

---

```cpp
template <typename T>
vector<int> compress(vector<T> &a) {
    int n = a.size();
    vector<int> ret(n);
    for (int i = 0; i < n; i++) ret[i] = a[i];
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    for (int i = 0; i < n; i++) a[i] = lower_bound(ret.begin(), ret.end(), a[i]) - ret.begin();
    return ret;
}
```