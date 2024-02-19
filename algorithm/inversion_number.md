[top](../README.md)

# [Inversion Number](./inversion.cpp)

`ll inversion_number(vector<int> a)`
- 数列 $a$ の転倒数を返す。
- $a$ の長さを $n$ として $0\leq a_i\le n$
- 重複要素があってもよい。
- $O(n\log{n})$

---

```cpp
long long inversion_number(const vector<int> &a) {
    int n = a.size();
    fenwick_tree<int> ft(n);
    long long ret = 0;
    for (int i = 0; i < n; i++) {
        ret += i - ft.sum(0, a[i]);
        ft.add(a[i], 1);
    }
    return ret;
}
```