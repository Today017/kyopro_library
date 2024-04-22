#include "../../kyopro_library/template.hpp"

template <typename T, bool MIN>
struct convex_hull_trick {
    convex_hull_trick() {}
    void add(T a, T b) {
        if (!MIN) {
            a *= -1, b *= -1;
        }
        pair<T, T> line(a, b);
        if (empty()) {
            dat.emplace_front(line);
            return;
        }
        if (dat.front().first <= a) {
            if (dat.front().first == a) {
                if (dat.front().second <= b) {
                    return;
                }
                dat.pop_front();
            }
            while (dat.size() >= 2 && check(line, dat.front(), dat[1])) {
                dat.pop_front();
            }
            dat.emplace_front(line);
        } else {
            assert(a <= dat.back().first);
            if (dat.back().first == a) {
                if (dat.back().second <= b) {
                    return;
                }
                dat.pop_back();
            }
            while (dat.size() >= 2 && check(dat[dat.size() - 2], dat.back(), line)) {
                dat.pop_back();
            }
            dat.emplace_back(line);
        }
    }
    inline T get_y(const pair<T, T> &a, const T &x) {
        return a.first * x + a.second;
    }
    T query(T x) {
        assert(!empty());
        int l = -1, r = dat.size() - 1;
        while (l + 1 < r) {
            int m = (l + r) >> 1;
            if (get_y(dat[m], x) >= get_y(dat[m + 1], x)) {
                l = m;
            } else {
                r = m;
            }
        }
        if (MIN) {
            return get_y(dat[r], x);
        }
        return -get_y(dat[r], x);
    }
    T query_monotone_inc(T x) {
        assert(!empty());
        while (dat.size() >= 2 && get_y(dat.front(), x) >= get_y(dat[1], x)) {
            dat.pop_front();
        }
        if (MIN) {
            return get_y(dat.front(), x);
        }
        return -get_y(dat.front(), x);
    }
    T query_monotone_dec(T x) {
        assert(!empty());
        while (dat.size() >= 2 && get_y(dat.back(), x) >= get_y(dat[dat.size() - 2], x)) {
            dat.pop_back();
        }
        if (MIN) {
            return get_y(dat.back(), x);
        }
        return -get_y(dat.back(), x);
    }
private:
    deque<pair<T, T>> dat;
    inline int sgn(T x) {
        return x == 0 ? 0 : (x < 0 ? -1 : 1);
    }
    bool empty() const {
        return dat.empty();
    }
    void clear() {
        dat.clear();
    }
    inline bool check(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> &c) {
        if (b.second == a.second || c.second == b.second) {
            return sgn(b.first - a.first) * sgn(c.second - b.second) >= sgn(c.first - b.first) * sgn(b.second - a.second);
        }
        long double left = (long double)(b.first - a.first) * sgn(c.second - b.second) / (long double)(abs(b.second - a.second));
        long double right = (long double)(c.first - b.first) * sgn(b.second - a.second) / (long double)(abs(c.second - b.second));
        return left >= right;
    }
};