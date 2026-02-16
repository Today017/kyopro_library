#include"../../kyopro_library/template.hpp"

///@brief 区間スケジューリングの応用（区間と1点のマッチング）
///@brief 与えられる区間列に対し、[0,M)の点を被りの無いように割り当てられるかを判定する
///@note O((N+M) log M)
///@ref https://atcoder.jp/contests/awc0004/tasks/awc0004_d
bool AssignPointsToRanges(vector<pair<int,int>> LR, int M) {
    vector<vector<int>> rs(M);
    for(auto [l,r]: LR) rs[l].push_back(r);
    priority_queue<int,vector<int>,greater<int>> pq;
    rep(x,M) {
        for(int r: rs[x]) pq.push(r);
        if(!pq.empty() && pq.top()<=x) return false;
        if(!pq.empty()) pq.pop();
    }
    return pq.empty();
}
