#include"../../kyopro_library/template.hpp"

///@brief 区間被覆問題
///@brief 与えられた区間から選んで[0,M)を覆うような最小個数を求める
///@brief 不可能な場合は-1を返す
///@note O(N log(N))
///@ref https://atcoder.jp/contests/awc0006/tasks/awc0006_d
int RangeCover(vector<pair<ll,ll>> LR, ll M) {
    int N=LR.size();
    sort(all(LR));

    int ret=0, idx=0;
    ll cur=0;
    priority_queue<ll> pq;
    while(cur<M) {
        while(idx<N && LR[idx].first<=cur) {
            pq.push(LR[idx].second);
            idx++;
        }
        if(pq.empty()) return -1;
        cur=pq.top(); pq.pop();
        ret++;
    }

    return ret;
}
