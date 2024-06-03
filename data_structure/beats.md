[top](../README.md)

# [Segment Tree Beats!](./beats.hpp)

`AngelBeats(int n)`

`AngelBeats(const vector<ll>& a)`

`void range_chmin(int l, int r, ll x)`
- $[l, r)$ の要素に対して、`a[i] = min(a[i], x)` を行う。
- $O(\log N)$

`void range_chmax(int l, int r, ll x)`
- $[l, r)$ の要素に対して、`a[i] = max(a[i], x)` を行う。
- $O(\log N)$

`void range_add(int l, int r, ll x)`
- $[l, r)$ の要素に対して、`a[i] += x` を行う。
- $O(\log N)$

`void range_update(int l, int r, ll x)`
- $[l, r)$ の要素に対して、`a[i] = x` を行う。
- $O(\log N)$

`ll range_min(int l, int r)`
- $[l, r)$ の要素の最小値を返す。
- $O(\log N)$

`ll range_max(int l, int r)`
- $[l, r)$ の要素の最大値を返す。
- $O(\log N)$

`ll range_sum(int l, int r)`
- $[l, r)$ の要素の合計値を返す。
- $O(\log N)$
