#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief 転倒数
/// @brief 配列 V の転倒数を求める
/// @note O(N log(N))時間 / O(N log(N))空間
ll InversionNumber(const vi& V) {
    // 座圧する必要がない代わりに空間がΘ(N log(N)) どっちがいいんだろうね
    ll ret = 0;
    auto Merge = [&](const vi& A, const vi& B) {
        int N = A.size();
        int r = 0;
        rep(l, N) {
            while(r < N && B[r] < A[l]) r++;
            ret += r;
        }
        vi c(2 * N);
        merge(all(A), all(B), c.begin());
        return c;
    };

    int N = V.size(), N2 = 1;
    while(N2 < N) N2 <<= 1;
    vector<vi> node(N2 << 1, vi(1, INFL));
    rep(i, N) node[i + N2] = {V[i]};
    for(int i = N2 - 1; i > 0; i--) node[i] = Merge(node[i << 1], node[i << 1 | 1]);
    return ret;
}

#include "../../kyopro_library/data_structure/fenwick_tree.hpp"

/// @brief 転倒数（座圧するバージョン）
/// @brief 配列 V の転倒数を求める
/// @note 座圧が必要
ll InversionNumber2(const vi& V) {
    int N = V.size();
    auto vals = V;
    sort(all(vals));
    vals.erase(unique(all(vals)), vals.end());
    int M = vals.size();
    FenwickTree fen(M);
    ll ret = 0;
    rep(i, N) {
        int x = lower_bound(all(vals), V[i]) - vals.begin();
        ret += fen.sum(x + 1, M);
        fen.add(x, 1);
    }
    return ret;
}
