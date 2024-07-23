#include "../../kyopro_library/template.hpp"

template <typename T>
struct SegmentTreeDual {
    using F = function<T(T, T)>;
    SegmentTreeDual() = default;
    SegmentTreeDual(int n, F f, T e) {
        this->n = n;
        this->f = f;
        this->e = e;
        dat = vector<T>(n << 1, e);
    }
    void build(const vector<T> &a) {
        assert((int)a.size() == n);
        for (int i = 0; i < (int)a.size(); i++) {
            dat[i + n] = a[i];
        }
    }
    T operator[](int i) {
        assert(0 <= i && i < n);
        i += n;
        T ret = e;
        while (i) {
            ret = f(ret, dat[i]);
            i >>= 1;
        }
        return ret;
    }
    void apply(int l, int r, T x) {
        assert(0 <= l && l <= r && r <= n);
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                dat[l] = f(dat[l], x);
                l++;
            }
            if (r & 1) {
                r--;
                dat[r] = f(dat[r], x);
            }
            l >>= 1;
            r >>= 1;
        }
    }

private:
    int n;
    vector<T> dat;
    F f;
    T e;
};

SegmentTreeDual<ll> RangeAddQuery(int n) {
    return SegmentTreeDual<ll>(n, [](ll a, ll b) { return a + b; }, 0);
}
template <typename T>
SegmentTreeDual<pair<T, int>> RangeUpdateQuery(int n) {
    auto f = [](pair<T, int> a, pair<T, int> b) {
        return a.second > b.second ? a : b;
    };
    return SegmentTreeDual<pair<T, int>>(n, f, {0, -1});
}