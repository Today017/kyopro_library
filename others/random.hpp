#pragma once
#include "../../kyopro_library/template.hpp"

namespace RandomGenerator {
    mt19937_64 generate;
    void init() {
        random_device seed_gen;
        generate = mt19937_64(seed_gen());
    }
    template <typename T>
    T randomInt(T x) {
        assert(x > 0);
        return generate() % x;
    }
    template <typename T>
    T randomInt(T x, T y) {
        assert(x < y);
        return x + generate() % (y - x);
    }
    template <typename T>
    T getElement(vector<T>& a) {
        const int n = a.size();
        int idx = randomInt(0, n);
        swap(a[n - 1], a[idx]);
        int ret = a.back();
        a.pop_back();
        return ret;
    }
    template <typename T>
    vector<T> randomArray(int n, T lo, T hi, bool no_dup = false) {
        vector<T> ret(n);
        if (!no_dup) {
            for (int i = 0; i < n; i++) ret[i] = randomInt(lo, hi);
        } else {
            set<T> st;
            for (int i = 0; i < n; i++) {
                int r = randomInt(lo, hi);
                while (st.count(r)) r = randomInt(lo, hi);
                ret[i] = r;
                st.insert(r);
            }
        }
        return ret;
    }
    string randomAlphabet(int n, bool lower = true) {
        string ret;
        for (int i = 0; i < n; i++) {
            int idx = randomInt(26);
            ret.push_back(char((lower ? 'a' : 'A') + idx));
        }
        return ret;
    }
    string randomString(int n, string s) {
        string ret;
        int m = s.size();
        for (int i = 0; i < n; i++) {
            int idx = randomInt(m);
            ret.push_back(s[idx]);
        }
        return ret;
    }
    template <typename T>
    vector<vector<T>> randomArray2D(int h, int w, T lo, T hi) {
        vector<vector<T>> ret(h, vector<T>(w));
        for (int i = 0; i < h; i++) ret[i] = randomArray(w, lo, hi);
        return ret;
    }
    vector<string> randomAlphabet2D(int h, int w, bool lower = true) {
        vector<string> ret(h);
        for (int i = 0; i < h; i++) ret[i] = randomAlphabet(w, lower);
        return ret;
    }
    vector<pair<int, int>> randomTree(int n) {
        vector<int> a = randomArray<int>(n - 2, 1, n + 1);
        vector<int> d(n + 1);
        for (int i = 0; i < n - 2; i++) d[a[i]]++;
        for (int i = 1; i <= n; i++) d[i]++;
        vector<pair<int, int>> ret;
        set<int> pq;
        for (int i = 1; i <= n; i++) {
            if (d[i] == 1) pq.insert(i);
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
    vector<pair<int, int>> randomBinaryTree(int n) {
        vector<pair<int, int>> ret;
        vector<ll> roots = {randomInt(1, n + 1)};
        vector<ll> leaves;
        for (int i = 1; i <= n; i++) {
            if (i != roots.back()) leaves.push_back(i);
        }
        while (!leaves.empty()) {
            int root = getElement(roots);
            int leaf = getElement(leaves);
            ret.push_back(make_pair(root, leaf));
            roots.push_back(leaf);
            if (!leaves.empty()) {
                int leaf = getElement(leaves);
                ret.push_back(make_pair(root, leaf));
                roots.push_back(leaf);
            }
        }
        return ret;
    }
    vector<pair<int, int>> randomUndirectedGraph(int n, int m, bool connected = true) {
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) edges.push_back(make_pair(i + 1, j + 1));
        }
        int ed = edges.size();
        if (!connected) {
            vector<pair<int, int>> ret;
            vector<int> idxs = randomArray<int>(m, 0, ed, true);
            for (int idx : idxs) ret.push_back(edges[idx]);
            return ret;
        } else {
            vector<pair<int, int>> ret;
            while (true) {
                ret.clear();
                vector<int> idxs = randomArray<int>(m, 0, ed, true);
                vector<int> parent(n);
                vector<vector<int>> sets(n);
                for (int i = 0; i < n; i++) {
                    parent[i] = i;
                    sets[i].push_back(i);
                }
                for (int idx : idxs) {
                    ret.push_back(edges[idx]);
                    auto [a, b] = edges[idx];
                    a--;
                    b--;
                    if (parent[a] != parent[b]) {
                        if (sets[parent[a]].size() < sets[parent[b]].size()) swap(a, b);
                        for (int x : sets[parent[b]]) {
                            parent[x] = parent[a];
                            sets[parent[a]].push_back(x);
                        }
                        sets[parent[b]].clear();
                    }
                }
                bool ok = true;
                for (int i = 0; i < n; i++) {
                    if (parent[i] != parent[0]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return ret;
            }
        }
    }
};  // namespace randomGenerator

struct SetupRandom {
    SetupRandom() {
        RandomGenerator::init();
    }
} setup_random_instance;