#include "../../.kyopro_library/template.cpp"

template <typename T, bool isMin>
struct ConvexHullTrickAddMonotone {
    using P = pair<T, T>;
    deque<P> H;
    ConvexHullTrickAddMonotone() = default;
    bool empty() const {
        return H.empty();
    }
    void clear() {
        H.clear();
    }
    inline int sgn(T x) {
        return x == 0 ? 0 : (x < 0 ? -1 : 1);
    }
    using ld = long double;
    inline bool check(const P &a, const P &b, const P &c) {
        if (b.second == a.second || c.second == b.second) return sgn(b.first - a.first) * sgn(c.second - b.second) >= sgn(c.first - b.first) * sgn(b.second - a.second);
        return ld(b.first - a.first) * sgn(c.second - b.second) / ld(abs(b.second - a.second)) >= ld(c.first - b.first) * sgn(b.second - a.second) / ld(abs(c.second - b.second));
    }
    void add(T a, T b) {
        if (!isMin) a *= -1, b *= -1;
        P line(a, b);
        if (empty()) {
            H.emplace_front(line);
            return;
        }
        if (H.front().first <= a) {
            if (H.front().first == a) {
                if (H.front().second <= b) return;
                H.pop_front();
            }
            while (H.size() >= 2 && check(line, H.front(), H[1])) H.pop_front();
            H.emplace_front(line);
        } else {
            assert(a <= H.back().first);
            if (H.back().first == a) {
                if (H.back().second <= b) return;
                H.pop_back();
            }
            while (H.size() >= 2 && check(H[H.size() - 2], H.back(), line)) H.pop_back();
            H.emplace_back(line);
        }
    }
    inline T get_y(const P &a, const T &x) {
        return a.first * x + a.second;
    }
    T query(T x) {
        assert(!empty());
        int l = -1, r = H.size() - 1;
        while (l + 1 < r) {
            int m = (l + r) >> 1;
            if (get_y(H[m], x) >= get_y(H[m + 1], x)) {
                l = m;
            } else {
                r = m;
            }
        }
        if (isMin) return get_y(H[r], x);
        return -get_y(H[r], x);
    }
    T query_monotone_inc(T x) {
        assert(!empty());
        while (H.size() >= 2 && get_y(H.front(), x) >= get_y(H[1], x)) H.pop_front();
        if (isMin) return get_y(H.front(), x);
        return -get_y(H.front(), x);
    }
    T query_monotone_dec(T x) {
        assert(!empty());
        while (H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) H.pop_back();
        if (isMin) return get_y(H.back(), x);
        return -get_y(H.back(), x);
    }
};