#include "../../kyopro_library/template.cpp"
#include "../../kyopro_library/graph/dsu.cpp"

namespace random_generator {
    mt19937_64 generate;
    void init() {
        random_device seed_gen;
        generate = mt19937_64(seed_gen());
    }
    template <typename T>
    T randint(T x) {
        assert(x > 0);
        return generate() % x;
    }
    template <typename T>
    T randint(T x, T y) {
        assert(x < y);
        return x + generate() % (y - x);
    }
    template <typename T>
    T get_elememt(vector<T>& a) {
        const int n = a.size();
        int idx = randint(0, n);
        swap(a[n - 1], a[idx]);
        int ret = a.back();
        a.pop_back();
        return ret;
    }
    template <typename T>
    vector<T> random_array_int(int n, T lo, T hi, bool no_dup = false) {
        vector<T> ret(n);
        if (!no_dup) {
            for (int i = 0; i < n; i++) {
                ret[i] = randint(lo, hi);
            }
        } else {
            set<T> st;
            for (int i = 0; i < n; i++) {
                int r = randint(lo, hi);
                while (st.count(r)) {
                    r = randint(lo, hi);
                }
                ret[i] = r;
                st.insert(r);
            }
        }
        return ret;
    }
    string random_alphabet(int n, bool lower = true) {
        string ret;
        for (int i = 0; i < n; i++) {
            int idx = randint(26);
            ret.push_back(char((lower ? 'a' : 'A') + idx));
        }
        return ret;
    }
    string random_string(int n, string s) {
        string ret;
        int m = s.size();
        for (int i = 0; i < n; i++) {
            int idx = randint(m);
            ret.push_back(s[idx]);
        }
        return ret;
    }
    template <typename T>
    vector<vector<T>> random_array_2D(int h, int w, T lo, T hi) {
        vector<vector<T>> ret(h, vector<T>(w));
        for (int i = 0; i < h; i++) {
            ret[i] = random_array_int(w, lo, hi);
        }
        return ret;
    }
    vector<string> random_alphabet_2D(int h, int w, bool lower = true) {
        vector<string> ret(h);
        for (int i = 0; i < h; i++) {
            ret[i] = random_alphabet(w, lower);
        }
        return ret;
    }
    vector<pair<int, int>> random_tree(int n) {
        vector<int> a = random_array_int<int>(n - 2, 1, n + 1);
        vector<int> d(n + 1);
        for (int i = 0; i < n - 2; i++) {
            d[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            d[i]++;
        }
        vector<pair<int, int>> ret;
        set<int> pq;
        for (int i = 1; i <= n; i++) {
            if (d[i] == 1) {
                pq.insert(i);
            }
        }
        for (int i = 0; i < n - 2; i++) {
            int v = (*pq.begin());
            pq.erase(v);
            ret.push_back(make_pair(v, a[i]));
            d[v]--;
            d[a[i]]--;
            if (d[a[i]] == 1) {
                pq.insert(a[i]);
            } else if (d[a[i]] == 0) {
                pq.erase(a[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (d[i] == 1) {
                for (int j = i + 1; j <= n; j++) {
                    if (d[j] == 1) {
                        ret.push_back(make_pair(i, j));
                        break;
                    }
                }
                break;
            }
        }
        return ret;
    }
    vector<pair<int, int>> random_bintree(int n) {
        vector<pair<int, int>> ret;
        vector<ll> roots = {randint(1, n + 1)};
        vector<ll> leaves;
        for (int i = 1; i <= n; i++) {
            if (i != roots.back()) {
                leaves.push_back(i);
            }
        }
        while (!leaves.empty()) {
            int root = get_elememt(roots);
            int leaf = get_elememt(leaves);
            ret.push_back(make_pair(root, leaf));
            roots.push_back(leaf);
            if (!leaves.empty()) {
                int leaf = get_elememt(leaves);
                ret.push_back(make_pair(root, leaf));
                roots.push_back(leaf);
            }
        }
        return ret;
    }
    vector<pair<int, int>> random_undigraph(int n, int m, bool connected = true) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.push_back(make_pair(i + 1, j + 1));
            }
        }
        int ed = edges.size();
        if (!connected) {
            vector<pair<int, int>> ret;
            vector<int> idxs = random_array_int<int>(m, 0, ed, true);
            for (int idx : idxs) {
                ret.push_back(edges[idx]);
            }
            return ret;
        } else {
            vector<pair<int, int>> ret;
            while (true) {
                ret.clear();
                vector<int> idxs = random_array_int<int>(m, 0, ed, true);
                disjoint_set_union ds(n);
                for (int idx : idxs) {
                    ret.push_back(edges[idx]);
                    auto [a, b] = edges[idx];
                    ds.unite(--a, --b);
                }
                bool ok = true;
                for (int i = 0; i < n; i++) {
                    if (ds.is_united(i, 0)) {
                        ok = false;
                    }
                }
                if (ok) return ret;
            }
        }
    }
};  // namespace random_generator
