#include "../../kyopro_library/template.hpp"

vector<pair<ll,ll>> ConvexHull(vector<pair<ll,ll>> p) {
    auto cross=[](const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c) {
        return
            (b.first-a.first)*(c.second-a.second)
            -(b.second-a.second)*(c.first-a.first);
    };
    sort(all(p));

    ll n=p.size();
    vector<pair<ll,ll>> ret; int k=0;
    rep(i,n) {
        while(k>1 && cross(ret[k-1],ret[k-2],p[i])>0) ret.pop_back(), k--;
        ret.push_back(p[i]); k++;
    }
    ll t=k;
    for(ll i=n-2; i>=0; i--) {
        while(k>t && cross(ret[k-1],ret[k-2],p[i])>0) ret.pop_back(), k--;
        ret.push_back(p[i]); k++;
    }
    set<pair<ll,ll>> seen;
    vector<pair<ll,ll>> newret;
    for(auto p: ret) if(!seen.count(p)) newret.push_back(p), seen.insert(p);

    return newret;
}
