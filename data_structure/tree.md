[top](../README.md)

# [Sorted Tree](./tree.hpp)

`tree<T>`
- 順序付き集合を管理するデータ構造。

`T max()`
- 最大値を求める。

`T min()`
- 最小値を求める。

`T pop_max()`
- 最大値を返し、削除する。

`T pop_min()`
- 最小値を返し、削除する。

`bool discard(T x)`
- 要素 $x$ を削除する。存在しない場合は `false` を返す。

`T gt(T x)`
- $x$ より大きい最小の値を返す。存在しない場合は `NULL` を返す。

`T ge(T x)`
- $x$ 以上の最小の値を返す。存在しない場合は `NULL` を返す。

`T lt(T x)`
- $x$ 未満最大の値を返す。存在しない場合は `NULL` を返す。

`T le(T x)`
- $x$ 以下最大の値を返す。存在しない場合は `NULL` を返す。

`T kth_min(int k)`
- $k$ 番目に小さい値を返す。`0-indexed` であることに注意。

`T kth_max(int k)`
- $k$ 番目に大きい値を返す。

`int count_lt(T x)`
- $x$ 未満の要素の個数を返す。

`int count_le(T x)`
- $x$ 以下の要素の個数を返す。

`int count_gt(T x)`
- $x$ より大きい要素の個数を返す。

`int count_gt(T x)`
- $x$ 以上の要素の個数を返す。

`bool contains(T x)`
- $x$ が含まれているか否かを返す。

---

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
struct sorted_tree : tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> {
    T max() {
        return *this->rbegin();
    }
    T min() {
        return *this->begin();
    }
    T pop_max() {
        T ret = max();
        this->erase(ret);
        return ret;
    }
    T pop_min() {
        T ret = min();
        this->erase(ret);
        return ret;
    }
    bool discard(T x) {
        auto itr = this->find(x);
        if (itr == this->end()) {
            return false;
        }
        this->erase(itr);
        return true;
    }
    T gt(T x) {
        auto itr = this->upper_bound(x);
        if (itr == this->end()) {
            return NULL;
        }
        return *itr;
    }
    T ge(T x) {
        auto itr = this->lower_bound(x);
        if (itr == this->end()) {
            return NULL;
        }
        return *itr;
    }
    T lt(T x) {
        auto itr = this->lower_bound(x);
        if (itr == this->begin()) {
            return NULL;
        }
        return *--itr;
    }
    T le(T x) {
        auto itr = this->upper_bound(x);
        if (itr == this->begin()) {
            return NULL;
        }
        return *--itr;
    }
    T kth_min(int k) {
        return *this->find_by_order(k);
    }
    T kth_max(int k) {
        return *this->find_by_order(this->size() - k - 1);
    }
    int count_lt(T x) {
        return this->order_of_key(x);
    }
    int count_le(T x) {
        return this->order_of_key(x + 1);
    }
    int count_gt(T x) {
        return this->size() - this->order_of_key(x + 1);
    }
    int count_ge(T x) {
        return this->size() - this->order_of_key(x);
    }
    bool contains(T x) {
        return this->find(x) != this->end();
    }
};
```