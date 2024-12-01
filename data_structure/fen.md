[top](../README.md)

# [Fenwick Tree](./fen.hpp)

`FenwickTree<Abel>(int n)`
- サイズ $n$ の Fenwick Tree を構築する。
- 可換群が乗る。

`Abel::Type add(int i, Abel::Type x)`
- 要素 $i$ に $x$ を加算する。
- $O(\log n)$

`Abel::Type sum(int l, int r)`
- $[l, r)$ の和を返す。
- $O(\log n)$


### 区間加算1点取得を行う場合
```cpp
fenwick_tree<> ft(N + 1);

// [l, r]に区間加算
ft.add(l, x);
ft.add(r + 1, x);

// i番目を取得
ft.sum(i + 1);
```