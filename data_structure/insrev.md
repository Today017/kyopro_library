[top](../README.md)

# [Insertable Reversible Array](./insrev.hpp)

`insertable_reversible_array(int n)`
`insertable_reversible_array(vector<T> a)`
- Insertable Reversible Array は挿入・削除・区間反転可能な配列である。

`void insert(i, x)`
- $i$ 番目に $x$ を挿入する。
- $O(\log n)$

`void erase(i)`
- $i$ 番目の要素を削除する。
- $O(\log n)$

`void reverse(i, j)`
- 区間 $[i, j)$ の要素を反転する。
- $O(\log n)$

`ll get(i)`
- $i$ 番目の要素を取得する。
- $O(\log n)$

`void set(i, x)`
- $i$ 番目の要素を $x$ に変更する。
- $O(\log n)$

`int size()`
- 配列のサイズを取得する。
- $O(1)$
