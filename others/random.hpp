#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/xor128.hpp"
#include "../../kyopro_library/others/shuffle.hpp"

/// @brief ランダムテストケース生成
namespace Rand {
    /// @brief 0 以上 n 未満のランダムな整数を返す
    template <typename T>
    T Int(T n) { return Xor128(n); }

    /// @brief [l, r) の範囲からランダムな整数を返す
    template <typename T>
    T Int(T l, T r) { return Xor128(l, r); }

    /// @brief 配列 a からランダムな要素を取得し、削除する
    template <typename T>
    T GetElement(vector<T>& a) {
        const int n = a.size();
        int idx = Int(0, n);
        swap(a[n - 1], a[idx]);
        int ret = a.back();
        a.pop_back();
        return ret;
    }

    /// @brief 長さ n の [lo, hi) の要素からなるランダムな数列を返す
    /// @param no_dup false の場合、重複要素を許容する
    template <typename T>
    vector<T> Array(int n, T lo, T hi, bool no_dup = false) {
        vector<T> ret(n);
        if(!no_dup) rep(i, n) ret[i] = Int(lo, hi);
        else {
            set<T> st;
            rep(i, n) {
                int r = Int(lo, hi);
                while(st.count(r)) r = Int(lo, hi);
                ret[i] = r;
                st.insert(r);
            }
        }
        return ret;
    }

    /// @brief ランダムなアルファベット文字列を返す
    /// @param lower 小文字
    string Alphabet(int n, bool lower = true) {
        string ret;
        rep(i, n) {
            int idx = Int(26);
            ret.push_back(char((lower ? 'a' : 'A') + idx));
        }
        return ret;
    }

    /// @brief 文字列 s の要素からなるランダムな文字列を返す
    string String(int n, string s) {
        string ret;
        int m = s.size();
        rep(i, n) {
            int idx = Int(m);
            ret.push_back(s[idx]);
        }
        return ret;
    }

    template <typename T>
    vector<vector<T>> Array2D(int h, int w, T lo, T hi) {
        vector<vector<T>> ret(h, vector<T>(w));
        rep(i, h) ret[i] = Array(w, lo, hi);
        return ret;
    }

    vector<string> Alphabet2D(int h, int w, bool lower = true) {
        vector<string> ret(h);
        rep(i, h) ret[i] = Alphabet(w, lower);
        return ret;
    }

    vector<pair<int, int>> Tree(int n) {
        auto a = Array<int>(n - 2, 1, n + 1);
        vi d(n + 1);
        rep(i, n - 2) d[a[i]]++;
        for(ll i = 1; i <= n; i++) d[i]++;
        vector<pair<int, int>> ret;
        set<int> pq;
        for(ll i = 1; i <= n; i++)
            if(d[i] == 1) pq.insert(i);
        rep(i, n - 2) {
            int v = (*pq.begin());
            pq.erase(v);
            ret.push_back(make_pair(v, a[i]));
            d[v]--;
            d[a[i]]--;
            if(d[a[i]] == 1) pq.insert(a[i]);
            else if(d[a[i]] == 0) pq.erase(a[i]);
        }
        for(ll i = 1; i <= n; i++) {
            if(d[i] == 1) {
                for(int j = i + 1; j <= n; j++)
                    if(d[j] == 1) {
                        ret.push_back(make_pair(i, j));
                        break;
                    }
                break;
            }
        }
        return ret;
    }

    vector<pair<int, int>> BinaryTree(int n) {
        vector<pair<int, int>> ret;
        vector<ll> roots = {Int(1, n + 1)}, leaves;
        for(ll i = 1; i <= n; i++)
            if(i != roots.back()) leaves.push_back(i);
        while(!leaves.empty()) {
            int root = GetElement(roots);
            int leaf = GetElement(leaves);
            ret.push_back(make_pair(root, leaf));
            roots.push_back(leaf);
            if(!leaves.empty()) {
                int leaf = GetElement(leaves);
                ret.push_back(make_pair(root, leaf));
                roots.push_back(leaf);
            }
        }
        return ret;
    }

    vector<pair<int, int>> UndirectedGraph(int n, int m, bool connected = true) {
        vector<pair<int, int>> edges;
        rep(i, n) for(int j = i + 1; j < n; j++) edges.push_back(make_pair(i + 1, j + 1));
        int ed = edges.size();
        if(!connected) {
            vector<pair<int, int>> ret;
            auto idxs = Array<int>(m, 0, ed, true);
            for(int idx : idxs) ret.push_back(edges[idx]);
            return ret;
        } else {
            vector<pair<int, int>> ret;
            while(true) {
                ret.clear();
                auto idxs = Array<int>(m, 0, ed, true);
                vi parent(n);
                vector<vi> sets(n);
                rep(i, n) {
                    parent[i] = i;
                    sets[i].push_back(i);
                }
                for(int idx : idxs) {
                    ret.push_back(edges[idx]);
                    auto [a, b] = edges[idx];
                    a--;
                    b--;
                    if(parent[a] != parent[b]) {
                        if(sets[parent[a]].size() < sets[parent[b]].size()) swap(a, b);
                        for(int x : sets[parent[b]]) {
                            parent[x] = parent[a];
                            sets[parent[a]].push_back(x);
                        }
                        sets[parent[b]].clear();
                    }
                }
                bool ok = true;
                rep(i, n) if(parent[i] != parent[0]) {
                    ok = false;
                    break;
                }
                if(ok) return ret;
            }
        }
    }
};  // namespace Rand
