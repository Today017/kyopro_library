#include"../../kyopro_library/template.hpp"

///@brief 2次元imos法
///@ref verify: https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_i
///@ref verify: https://atcoder.jp/contests/abc435/tasks/abc435_e
struct Imos2D {
    Imos2D(int h, int w): h(h), w(w), dat(vector<vector<ll>>(h+1,vector<ll>(w+1))) {}
    void add(int u, int d, int l, int r, ll x) {
        dat[u][l]+=x; dat[u][r]-=x; dat[d][l]-=x; dat[d][r]+=x;
    }
    void build() {
        rep(i,h) rep(j,w+1) dat[i+1][j]+=dat[i][j];
        rep(i,h+1) rep(j,w) dat[i][j+1]+=dat[i][j];
    }
    ll get(int i, int j) { return dat[i][j]; }

private:
    int h,w;
    vector<vector<ll>> dat;
};
