#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/mod/modint.hpp"

/// @brief 数論変換
/// @note O(N log(N))
/// @details f(x) = Σ A[i]x^i, w^N = 1 とすると、F(t) = Σ f(w^i)t^i の各係数 mod 998244353 に変換する
void NTT998(vector<Mod998>& A, bool inv = false) {
    static vector<Mod998> r, ir, tmp;
    if(r.empty()) {
        int dm = 1;
        ll N = Mod998::mod() - 1;
        while(N % 2 == 0) N >>= 1, dm++;
        r.resize(dm + 1);
        ir.resize(dm + 1);
        r[0] = ir[0] = 1;
        for(int i = 1; i <= dm; i++) {
            r[i] = Mod998(3).pow((Mod998::mod() - 1) >> i);
            ir[i] = r[i].inv();
        }
    }
    tmp.resize(A.size());
    int N = A.size(), p = 0;
    for(int i = N >> 1; i; i >>= 1, p++) {
        auto &cur = p & 1 ? tmp : A, &nxt = p & 1 ? A : tmp;
        Mod998 w = 1, e = inv ? r[p + 1] : ir[p + 1];
        for(int j = 0; j < N; j += i, w *= e) rep(k, i) {
                nxt[j + k] = cur[((j << 1) & (N - 1)) + k] + w * cur[(((j << 1) + i) & (N - 1)) + k];
            }
    }
    if(p & 1) swap(A, tmp);
    if(inv) {
        Mod998 in = Mod998(N).inv();
        for(Mod998& x : A) x *= in;
    }
}

/// @brief AとBの畳み込み C[i] = Σ A[j]B[i-j] mod 998244353 を返す
/// @note O(N log(N))
/// @attention |A|+|B| <= 2^23 が必要
/// @ref verify: https://judge.yosupo.jp/problem/convolution_mod
vector<Mod998> Convolve998(vector<Mod998> A, vector<Mod998> B) {
    int N = 1, z = A.size() + B.size();
    while(N + 1 < z) N <<= 1;
    A.resize(N);
    B.resize(N);
    NTT998(A);
    NTT998(B);
    rep(i, N) A[i] *= B[i];
    NTT998(A, true);
    while(A.size() + 1 > z) A.pop_back();
    return A;
}