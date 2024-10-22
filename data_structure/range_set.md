[top](../README.md)

# [Range Set](./range_set.hpp)

`RangeSet()`
- 区間を set で管理するデータ構造。
- 二分探索で挿入・削除位置を探し、左右の区間を調べてマージしたりする。

`void insert(ll l,ll r)`
- 区間 $[l,r)$ を追加する。
- $O(\log N)$

`void erase(ll l,ll r)`
- 区間 $[l,r)$ を削除する。
- $O(\log N)$

`bool is_covered(ll l,ll r)`
- 区間 $[l,r)$ が RangeSet に完全に被覆されているかどうかを判定する。
- $O(\log N)$

`pair<ll, ll> covering_range(ll x)`
- 点 $x$ を含む区間を返す。存在しない場合は `{-INFL, -INFL}` を返す。
- $O(\log N)$

---