#pragma once
#include <bits/stdc++.h>
using namespace std;

#define ALL(x) (x).begin(),(x).end()
#define IO ios::sync_with_stdio(false),cin.tie(nullptr);
#define LB(v, x) (ll)(lower_bound(ALL(v),x)-(v).begin())
#define UQ(v) sort(ALL(v)),(v).erase(unique(ALL(v)),v.end())
#define REP(i, n) for(ll i=0; i<(ll)(n); i++)
#define FOR(i, a, b) for(ll i=(ll)(a); (a)<(b) ? i<(b) : i>(b); i+=((a)<(b) ? 1 : -1))
#define chmax(a, b) ((a)<(b) ? ((a)=(b), 1) : 0)
#define chmin(a, b) ((a)>(b) ? ((a)=(b), 1) : 0)

template<typename T> using rpriority_queue=priority_queue<T,vector<T>,greater<T>>;
using ll=long long; const int INF=1e9+10; const ll INFL=4e18; using ld=long double; using ull=uint64_t;
using VI=vector<int>; using VVI=vector<VI>; using VL=vector<ll>; using VVL=vector<VL>;
using PL=pair<ll,ll>; using VP=vector<PL>; using TL=tuple<ll,ll,ll>; using WG=vector<vector<pair<int,ll>>>;

#ifdef LOCAL
#include "./debug.hpp"
#else
#define debug(...)
#define print_line
#endif