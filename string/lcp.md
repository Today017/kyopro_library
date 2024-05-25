[top](../README.md)

# [LCP Array](./lcp.hpp)

`vector<int> lcp_array(const T &s)`
- 文字列 $s(|s|=n)$ に対して、 $ret_i=$ 「suffix array において $i$ 番目の suffix と $i+1$ 番目の suffix の Longest Common Prefix の長さ」であるような配列 $ret$ を返す。
- $O(N)$