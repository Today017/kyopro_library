#include"../../kyopro_library/template.hpp"

/// @brief LIS
/// @brief 配列 v の最長増加部分列の長さを返す
/// @param strict `true` のとき狭義単調増加
/// @note O(N log(N))
int LisLength(vector<int>& v, bool strict=true) {
    int n=v.size();
    vector<int> dp(n,INF);
    for(int i=0; i<n; i++) {
        auto itr=(strict ? lower_bound(dp.begin(),dp.end(),v[i]) : upper_bound(dp.begin(),dp.end(),v[i]));
        *itr=v[i];
    }
    return find(dp.begin(),dp.end(),INF)-dp.begin();
}