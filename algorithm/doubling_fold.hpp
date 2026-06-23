#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief ダブリング（モノイド合成）
/// @tparam Monoid 合成するモノイド
/// @tparam Log ダブリングの深さ
template <typename Monoid, ii Log>
struct DoublingFold {
    using Type = typename Monoid::Type;
    DoublingFold() = default;

    /// @brief コンストラクタ
    /// @param P 各頂点の遷移先
    /// @param V 各頂点の値
    /// @note O(N Log)
    DoublingFold(const vi& P, const vector<Type>& V) {
        ii N = P.size();
        dat = vector<vector<Type>>(Log + 1, vector<Type>(N, Monoid::id()));
        nxt = vector<vi>(Log + 1, vi(N));
        rep(i, N) dat[0][i] = V[i], nxt[0][i] = P[i];
        rep(i, Log) rep(j, N) {
            nxt[i + 1][j] = nxt[i][nxt[i][j]];
            dat[i + 1][j] = Monoid::op(dat[i][j], dat[i][nxt[i][j]]);
        }
    }

    /// @brief (遷移先, モノイド積) を返す
    /// @brief 頂点 start から K 回遷移したときの頂点とモノイド積の組を返す
    /// @note O(Log)
    pair<ii, Type> fold(ii start, ll K) {
        Type ret = Monoid::id();
        rep(b, Log + 1) if(K >> b & 1) {
            ret = Monoid::op(ret, dat[b][start]);
            start = nxt[b][start];
        }
        return {start, ret};
    }

private:
    vector<vector<Type>> dat;
    vector<vi> nxt;
};