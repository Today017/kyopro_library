[top](../README.md)

# [Longest Increasing Subsequence](./lis.hpp)

`int lisLength(vector<int> v, bool strict = true)`
- 数列 $v$ の最長増加部分列の長さを返す。
- `strict` が `false` の場合、狭義単調増加列について数える。
- $O(n\log{n})$