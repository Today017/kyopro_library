[top](../README.md)

# [Convex Hull Trick](./cht.hpp)

`convex_hull_trick<T, MIN>`
- 直線を管理し、クエリに対して最小値、または最大値を求める。

`add(T a, T b)`
- 直線 $y = ax + b$ を追加する。
- 直線集合のサイズを $N$ として $O(\log N)$

`get(T x)`
- $x$ における最小値、または最大値を求める。
- $O(\log^2 N)$

---

```cpp
template <typename T = ll, bool MIN = true>
struct convex_hull_trick {
    convex_hull_trick() = default;
    void add(T a, T b) {
        if (!MIN) {
            a *= -1;
            b *= -1;
        }
        if (lines.count(a)) {
            if (lines[a] <= b) {
                return;
            }
        }
        lines[a] = b;
        auto it = lines.find(a);
        if (!need(it)) {
            lines.erase(a);
            return;
        }
        if (it != lines.begin()) {
            it = prev(it);
            while (true) {
                if (need(it)) {
                    break;
                }
                auto prv = prev(it);
                lines.erase(it);
                it = prv;
            }
        }
        it = next(lines.find(a));
        while (true) {
            if (need(it)) {
                break;
            }
            auto nxt = next(it);
            lines.erase(it);
            it = nxt;
        }
    }
    T get(T x) {
        T lo = lines.begin()->first, hi = lines.rbegin()->first + 1;
        while (hi - lo > 1) {
            T mid = (lo + hi) / 2;
            auto it = lines.lower_bound(mid);
            if (it == lines.begin()) {
                lo = mid;
                continue;
            }
            if (it == lines.end()) {
                hi = mid;
                continue;
            }
            auto [a1, b1] = *prev(it);
            auto [a2, b2] = *it;
            if (a1 * x + b1 <= a2 * x + b2) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        auto it = lines.lower_bound(lo);
        auto [a, b] = *it;
        return (a * x + b) * (MIN ? 1 : -1);
    }

private:
    map<T, T> lines;
    bool need(const typename map<T, T>::iterator it) {
        if (it == lines.begin() || it == prev(lines.end()) || it == lines.end()) {
            return true;
        }
        auto prv = prev(it);
        auto nxt = next(it);
        auto [a, b] = *it;
        auto [a1, b1] = *nxt;
        auto [a2, b2] = *prv;
        return (__int128)(a1 - a) * (b - b2) < (__int128)(a - a2) * (b1 - b);
    }
};

```
