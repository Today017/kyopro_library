[top](../README.md)

# [Inversion Number](./inversion_number.hpp)

`ll inversion_number(vector<int> a)`
- 数列 $a$ の転倒数を返す。
- $a$ の長さを $n$ として $0\leq a_i < n$ であることを要求する。
- 重複要素があってもよい。
- $O(n\log{n})$

---

```cpp
ll inversion_number(const vector<int> &a) {
    int n = a.size();
    fenwick_tree<int> ft(n);
    ll ret = 0;
    for (int i = 0; i < n; i++) {
        ret += i - ft.sum(0, a[i]);
        ft.add(a[i], 1);
    }
    return ret;
}
```