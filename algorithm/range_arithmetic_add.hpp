#include"../../kyopro_library/template.hpp"

/// @brief 区間等差数列加算（オフライン）
/// @brief 長さ n の数列に対する区間等差数列加算クエリを処理する
/// @brief クエリは `(l, r, start, step)` の形式で与える
/// @note O(N)
/// @ref verify: https://mojacoder.app/users/Today03/problems/range_arithmetic_add
/// @ref verify: https://atcoder.jp/contests/abc407/tasks/abc407_f
VL RangeArithmeticAdd(int n, vector<tuple<ll,ll,ll,ll>> query) {
    VL i1(n+10),i2(n+10);

    for(auto [l,r,start,step]:query) {
        i1[l+1]+=step; i1[r]-=step;
        i1[r]-=step*(r-l-1); i1[r+1]+=step*(r-l-1);
        i2[l]+=start; i2[r]-=start;
    }

    REP(i,n+5) i1[i+1]+=i1[i], i2[i+1]+=i2[i];

    VL ret(n);
    REP(i,n-1) ret[i+1]=ret[i]+i1[i+1];
    REP(i,n) ret[i]+=i2[i];

    return ret;
}