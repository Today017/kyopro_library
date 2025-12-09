#include"../../kyopro_library/template.hpp"

/// @brief 2次元累積和
struct Cumsum2D {
    Cumsum2D()=default;
    Cumsum2D(int h, int w):
        h(h), w(w),
        dat(vector<vector<ll>>(h+1,vector<ll>(w+1))),
        predat(vector<vector<ll>>(h,vector<ll>(w))) {}
    
    /// @brief 配列 v から2次元累積和テーブルを構築する
    Cumsum2D(const auto& v) {
        h=v.size(), w=v.front().size();
        dat=vector<vector<ll>>(h+1,vector<ll>(w+1));
        rep(i,h) rep(j,w) dat[i+1][j+1]=dat[i+1][j]+dat[i][j+1]-dat[i][j]+v[i][j];
    }
    /// @brief (i,j) に値 x を代入する
    /// @attention `build()` の前に呼び出すこと
    void set(int i, int j, ll x) { predat[i][j]=x; }
    /// @brief 2次元累積和を構築する
    void build() {
        rep(i,h) rep(j,w) dat[i+1][j+1]=dat[i+1][j]+dat[i][j+1]-dat[i][j]+predat[i][j];
    }
    /// @brief 矩形領域 [u, d) x [l, r) の値の和を返す
    ll sum(int u, int d, int l, int r) {
        return dat[d][r]-dat[d][l]-dat[u][r]+dat[u][l];
    }

private:
    int h,w;
    vector<vector<ll>> dat, predat;
};
