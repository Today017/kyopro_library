[top](../README.md)

# [Z Algorithm](./zalgo.hpp)

`vector<int> z_algorithm(string s)`
- 文字列 $s(|s|=n)$ に対して、 $ret_i=$ 「 $S[0,n)$ と $S[i,n)$ の Longest Common Prefix の長さ」であるような配列 $ret$ を返す。
- $O(N)$