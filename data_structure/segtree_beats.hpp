#include "../../kyopro_library/template.hpp"

/// @brief Segment Tree Beat!
/// @ref https://nyaannyaan.github.io/library/segment-tree/segment-tree-beats.hpp
struct AngelBeats {
    struct alignas(32) Node {
        ll sum = 0, g1 = 0, l1 = 0;
        ll g2 = -INFL, gc = 1, l2 = INFL, lc = 1, add = 0;
    };
    vector<Node> v;
    ll n, log;
    AngelBeats() {}
    AngelBeats(int _n) : AngelBeats(vector<ll>(_n)) {}
    AngelBeats(const vector<ll>& vc) {
        n = 1, log = 0;
        while (n < (int)vc.size()) n <<= 1, log++;
        v.resize(2 * n);
        for (ll i = 0; i < (int)vc.size(); ++i) {
            v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i];
        }
        for (ll i = n - 1; i; --i) update(i);
    }
    /// @brief [l, r) に対し、v[i] <- min(v[i], x)
    void range_chmin(int l, int r, ll x) { inner_apply<1>(l, r, x); }
    /// @brief [l, r) に対し、v[i] <- max(v[i], x)
    void range_chmax(int l, int r, ll x) { inner_apply<2>(l, r, x); }
    /// @brief [l, r) に対し、v[i] <- v[i] + x
    void range_add(int l, int r, ll x) { inner_apply<3>(l, r, x); }
    /// @brief [l, r) に対し、v[i] <- x
    void range_update(int l, int r, ll x) { inner_apply<4>(l, r, x); }
    /// @brief min[l, r)(v[i]) を返す
    ll range_min(int l, int r) { return inner_fold<1>(l, r); }
    /// @brief max[l, r)(v[i]) を返す
    ll range_max(int l, int r) { return inner_fold<2>(l, r); }
    /// @brief sum[l, r)(v[i]) を返す
    ll range_sum(int l, int r) { return inner_fold<3>(l, r); }

private:
    void update(int k) {
        Node& p = v[k];
        Node& l = v[k * 2 + 0];
        Node& r = v[k * 2 + 1];
        p.sum = l.sum + r.sum;
        if (l.g1 == r.g1) {
            p.g1 = l.g1;
            p.g2 = max(l.g2, r.g2);
            p.gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            p.g1 = f ? l.g1 : r.g1;
            p.gc = f ? l.gc : r.gc;
            p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }
        if (l.l1 == r.l1) {
            p.l1 = l.l1;
            p.l2 = min(l.l2, r.l2);
            p.lc = l.lc + r.lc;
        } else {
            bool f = l.l1 < r.l1;
            p.l1 = f ? l.l1 : r.l1;
            p.lc = f ? l.lc : r.lc;
            p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }
    }
    void push_add(int k, ll x) {
        Node& p = v[k];
        p.sum += x << (log + __builtin_clz(k) - 31);
        p.g1 += x;
        p.l1 += x;
        if (p.g2 != -INFL) p.g2 += x;
        if (p.l2 != INFL) p.l2 += x;
        p.add += x;
    }
    void push_min(int k, ll x) {
        Node& p = v[k];
        p.sum += (x - p.g1) * p.gc;
        if (p.l1 == p.g1) p.l1 = x;
        if (p.l2 == p.g1) p.l2 = x;
        p.g1 = x;
    }
    void push_max(int k, ll x) {
        Node& p = v[k];
        p.sum += (x - p.l1) * p.lc;
        if (p.g1 == p.l1) p.g1 = x;
        if (p.g2 == p.l1) p.g2 = x;
        p.l1 = x;
    }
    void push(int k) {
        Node& p = v[k];
        if (p.add != 0) {
            push_add(k * 2 + 0, p.add);
            push_add(k * 2 + 1, p.add);
            p.add = 0;
        }
        if (p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
        if (p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);
        if (p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
        if (p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
    }
    void subtree_chmin(int k, ll x) {
        if (v[k].g1 <= x) return;
        if (v[k].g2 < x) {
            push_min(k, x);
            return;
        }
        push(k);
        subtree_chmin(k * 2 + 0, x);
        subtree_chmin(k * 2 + 1, x);
        update(k);
    }
    void subtree_chmax(int k, ll x) {
        if (x <= v[k].l1) return;
        if (x < v[k].l2) {
            push_max(k, x);
            return;
        }
        push(k);
        subtree_chmax(k * 2 + 0, x);
        subtree_chmax(k * 2 + 1, x);
        update(k);
    }
    template <int cmd>
    inline void _apply(int k, ll x) {
        if constexpr (cmd == 1) subtree_chmin(k, x);
        if constexpr (cmd == 2) subtree_chmax(k, x);
        if constexpr (cmd == 3) push_add(k, x);
        if constexpr (cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
    }
    template <int cmd>
    void inner_apply(int l, int r, ll x) {
        if (l == r) return;
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) _apply<cmd>(l++, x);
                if (r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template <int cmd>
    inline ll e() {
        if constexpr (cmd == 1) return INFL;
        if constexpr (cmd == 2) return -INFL;
        return 0;
    }
    template <int cmd>
    inline void op(ll& a, const Node& b) {
        if constexpr (cmd == 1) a = min(a, b.l1);
        if constexpr (cmd == 2) a = max(a, b.g1);
        if constexpr (cmd == 3) a += b.sum;
    }
    template <int cmd>
    ll inner_fold(int l, int r) {
        if (l == r) return e<cmd>();
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        ll lx = e<cmd>(), rx = e<cmd>();
        while (l < r) {
            if (l & 1) op<cmd>(lx, v[l++]);
            if (r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr (cmd == 1) lx = min(lx, rx);
        if constexpr (cmd == 2) lx = max(lx, rx);
        if constexpr (cmd == 3) lx += rx;
        return lx;
    }
};