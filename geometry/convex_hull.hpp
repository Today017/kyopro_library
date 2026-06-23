#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief 凸包
vector<pair<ll, ll>> ConvexHull(vector<pair<ll, ll>> P) {
    auto cross = [](const pair<ll, ll>& a, const pair<ll, ll>& b, const pair<ll, ll>& c) {
        return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
    };
    sort(all(P));

    ll N = P.size();
    vector<pair<ll, ll>> ret;
    int k = 0;
    rep(i, N) {
        while(k > 1 && cross(ret[k - 1], ret[k - 2], P[i]) > 0) ret.pop_back(), k--;
        ret.push_back(P[i]);
        k++;
    }
    ll t = k;
    for(ll i = N - 2; i >= 0; i--) {
        while(k > t && cross(ret[k - 1], ret[k - 2], P[i]) > 0) ret.pop_back(), k--;
        ret.push_back(P[i]);
        k++;
    }
    set<pair<ll, ll>> seen;
    vector<pair<ll, ll>> newret;
    for(auto P : ret)
        if(!seen.count(P)) newret.push_back(P), seen.insert(P);

    return newret;
}
