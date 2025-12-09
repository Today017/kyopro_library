#include"../../kyopro_library/template.hpp"

/// @brief 2次元imos法
struct Imos2D {
    Imos2D(int h, int w): h(h), w(w), dat(vector<vector<ll>>(h+1,vector<ll>(w+1))) {}
    /// @brief 矩形領域 [u, d) x [l, r) に x を加算する
    void add(int u, int d, int l, int r, ll x) {
        dat[u][l]+=x; dat[u][r]-=x; dat[d][l]-=x; dat[d][r]+=x;
    }
    void build() {
        rep(i,h+1) if(i) rep(j,w+1) dat[i][j]+=dat[i-1][j];
        rep(i,h+1) rep(j,w+1) if(j) dat[i][j]+=dat[i][j-1];
    }
    /// @brief (i, j) の値を返す
    ll get(int i, int j) { return dat[i][j]; }

private:
    int h,w;
    vector<vector<ll>> dat;
};
