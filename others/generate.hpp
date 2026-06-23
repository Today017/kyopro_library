#pragma once
#include "../../kyopro_library/template.hpp"

namespace Gen {
    /// @brief 長さnの順列をすべて生成する
    vvi Permutations(ii n) {
        vi p = mkiota(n);
        vvi ret;
        do {
            ret.push_back(p);
        } while(next_permutation(all(p)));

        return ret;
    }

    /// @brief [0...n-1]からk個選ぶ方法を全探索する
    vvi Combinations(ii n, ii k) {
        vvi ret;
        vi c;
        auto dfs = [&](auto&& dfs, ii i) -> void {
            if(siz(c) == k) {
                ret.push_back(c);
                return;
            }
            if(i == n) return;

            c.push_back(i);
            dfs(dfs, i + 1);
            c.pop_back();

            if(siz(c) + (n - i - 1) >= k) dfs(dfs, i + 1);
        };
        dfs(dfs, 0);
        return ret;
    }

    /// @brief 長さn、要素[0,k)の数列をすべて生成する
    vvi Array(ii n, ii k) {
        vvi ret;
        vi seq;
        auto dfs = [&](auto&& dfs) -> void {
            if(siz(seq) == n) {
                ret.push_back(seq);
                return;
            }
            for(int i = 0; i < k; i++) {
                seq.push_back(i);
                dfs(dfs);
                seq.pop_back();
            }
        };
        dfs(dfs);
        return ret;
    };

    /// @brief 長さn、要素[0,k)のソート済み数列をすべて生成する
    vvi Sorted(ii n, ii k) {
        vvi ret;
        vi seq;
        auto dfs = [&](auto&& dfs) -> void {
            if(siz(seq) == n) {
                ret.push_back(seq);
                return;
            }
            int last = QYN(siz(seq), seq.back(), 0);
            for(int i = last; i < k; i++) {
                seq.push_back(i);
                dfs(dfs);
                seq.pop_back();
            }
        };
        dfs(dfs);
        return ret;
    };

    /// @brief 長さn、要素[0,k)のdistinctな数列をすべて生成する
    vvi Distinct(ii n, ii k) {
        vvi ret;
        vi seq, used(k);
        auto dfs = [&](auto&& dfs) -> void {
            if(siz(seq) == n) {
                ret.push_back(seq);
                return;
            }
            for(int i = 0; i < k; i++) {
                if(!used[i]) {
                    used[i] = 1;
                    seq.push_back(i);
                    dfs(dfs);
                    used[i] = 0;
                    seq.pop_back();
                }
            }
        };
        dfs(dfs);
        return ret;
    };

    /// @brief 長さn、要素[0,k)のソート済みのdistinctな数列をすべて生成する
    vvi SortedDistinct(ii n, ii k) {
        vvi ret;
        vi seq;
        auto dfs = [&](auto&& dfs) -> void {
            if(siz(seq) == n) {
                ret.push_back(seq);
                return;
            }
            int last = QYN(siz(seq), seq.back() + 1, 0);
            for(int i = last; i < k; i++) {
                if(siz(seq) + (k - i) < n) break;
                seq.push_back(i);
                dfs(dfs);
                seq.pop_back();
            }
        };
        dfs(dfs);
        return ret;
    };

    /// @brief 長さn、文字集合sからなる文字列をすべて生成する
    vstr String(ii n, str s) {
        ii k = siz(s);
        vvi gen = Array(n, k);
        vstr ret;
        for(vi g : gen) {
            ret.push_back("");
            for(ii i : g) ret.back().push_back(s[i]);
        }
        return ret;
    }
}  // namespace Gen
