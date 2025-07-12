VP ConvexHull(VP p) {
    auto cross=[](const PL& a, const PL& b, const PL& c) {
        return
            (b.first-a.first)*(c.second-a.second)
            -(b.second-a.second)*(c.first-a.first);
    };
    sort(ALL(p));

    ll n=p.size();
    VP ret; int k=0;
    REP(i,n) {
        while(k>1 && cross(ret[k-1],ret[k-2],p[i])>0) ret.pop_back(), k--;
        ret.push_back(p[i]); k++;
    }
    ll t=k;
    for(ll i=n-2; i>=0; i--) {
        while(k>t && cross(ret[k-1],ret[k-2],p[i])>0) ret.pop_back(), k--;
        ret.push_back(p[i]); k++;
    }
    set<PL> seen;
    VP newret;
    for(auto p: ret) if(!seen.count(p)) newret.push_back(p), seen.insert(p);

    return newret;
}
