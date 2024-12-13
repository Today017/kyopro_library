[top](../README.md)

# [Combinatorics](./cmb.hpp)

`Combinatorics(int n)`
- サイズ $n$ のテーブルを作成する。
- $O(n\log{n})$

`T comb(n, r)`
- ${}_n C_r$ を返す。
- $O(1)$

`T perm(n, r)`
- ${}_n P_r$ を返す。
- $O(1)$