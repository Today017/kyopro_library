#include"../../kyopro_library/template.hpp"

/// @brief 2次元累積和
/// @tparam T 群
template<typename T>
struct CumulativeSum2D {
    CumulativeSum2D()=default;

    /// @brief v から2次元累積和を構築する
    template<typename U>
    CumulativeSum2D(const vector<vector<U>>& v) {
        n=v.size(),m=v.front().size();
        dat.assign(n+1,vector<T>(m+1));
        for(int i=0; i<n; i++) for(int j=0; j<m; j++) {
            dat[i+1][j+1]=dat[i][j]+dat[i+1][j]-dat[i][j]+v[i][j];
        }
    }

    /// @brief 矩形領域 [l, r) × [u, d) の和を求める
    T sum(int l, int r, int u, int d) {
        return dat[r][d]-dat[l][d]-dat[r][u]+dat[l][u];
    }

private:
    int n,m;
    vector<vector<T>> dat;
};