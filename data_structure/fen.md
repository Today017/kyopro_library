[top](../README.md)

# [Fenwick Tree](./fen.hpp)

`T add(int i, T x)`
- $0\le i < n$
- $O(\log n)$

`T sum(int l, int r)`
- $0\le l < r\leq n$
- $O(\log n)$


### 区間加算1点取得を行う場合
```cpp
fenwick_tree<int> ft(N + 1);

// [l, r]に区間加算
ft.add(l, x);
ft.add(r + 1, x);

// i番目を取得
ft.sum(i + 1);
```