#include"../../kyopro_library/template.hpp"

///@brief LIS
///@brief 配列 v の最長増加部分列の長さを返す
///@param strict `true` のとき狭義単調増加
///@note O(N log(N))
int LisLength(vector<int>& v, bool strict=true) {
    int n=v.size();
    vector<int> dp(n,INF);
    rep(i,n) {
        int idx=(
            strict?
            lower_bound(all(dp),v[i]):
            upper_bound(all(dp),v[i])
        )-dp.begin();
        dp[idx]=v[i];
    }
    rep(i,n) if(dp[i]==INF) return i;
    return n;
}