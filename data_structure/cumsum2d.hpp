#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief 2次元累積和
/// @ref verify: https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_h
/// @ref verify: https://atcoder.jp/contests/abc435/tasks/abc435_e
struct Cumsum2D {
    Cumsum2D() = default;
    Cumsum2D(int H, int W) : H(H), W(W),
                             dat(vector<vector<ll>>(H + 1, vector<ll>(W + 1))),
                             predat(vector<vector<ll>>(H, vector<ll>(W))) {}

    /// @brief 配列 V から2次元累積和テーブルを構築する
    Cumsum2D(const auto& V) {
        H = V.size(), W = V.front().size();
        dat = vector<vector<ll>>(H + 1, vector<ll>(W + 1));
        rep(i, H) rep(j, W) dat[i + 1][j + 1] = dat[i + 1][j] + dat[i][j + 1] - dat[i][j] + V[i][j];
    }

    /// @brief (i,j) に値 x を代入する
    /// @attention `build()` の前に呼び出すこと
    void set(int i, int j, ll x) { predat[i][j] = x; }

    /// @brief 2次元累積和を構築する
    void build() {
        rep(i, H) rep(j, W) dat[i + 1][j + 1] = dat[i + 1][j] + dat[i][j + 1] - dat[i][j] + predat[i][j];
    }

    /// @brief 矩形領域 [u, d) x [l, r) の値の和を返す
    ll sum(int u, int d, int l, int r) {
        return dat[d][r] - dat[d][l] - dat[u][r] + dat[u][l];
    }

private:
    int H, W;
    vector<vector<ll>> dat, predat;
};
