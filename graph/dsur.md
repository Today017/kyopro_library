[top](../README.md)

# [Disjoint Set Union (Rollback)](./dsur.hpp)

`DsuRollback(int n)`
- Rollback 可能な DSU。

`void undo()`
- 直前の merge を取り消す。

`void snapshot()`
- DSU の状態を上書きする。

`void rollback()`
- 最後に snapshot を行った時点まで状態を巻き戻す。
