#pragma once
#include <bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for(ll i=0; i<(ll)(n); i++)
#define RREP(i, n) for(ll i=(ll)(n)-1; i>=0; i--)

template<typename T> int LB(const vector<T>& v, T x) { return lower_bound(ALL(v),x)-v.begin(); }
template<typename T> int UQ(T& v) { sort(ALL(v)); v.erase(unique(ALL(v)),v.end()); return v.size(); }
template<typename T> bool chmax(T& a, T b) { return a<b ? a=b, true : false; }
template<typename T> bool chmin(T& a, T b) { return a>b ? a=b, true : false; }
template<typename T> using rpriority_queue=priority_queue<T,vector<T>,greater<T>>;
using ll=long long; const int INF=1e9+10; const ll INFL=4e18;
using ld=long double; using lll=__int128_t; using ull=unsigned long long;
using VI=vector<int>; using VVI=vector<VI>; using VL=vector<ll>; using VVL=vector<VL>;
using PL=pair<ll,ll>; using VP=vector<PL>; using WG=vector<vector<pair<int,ll>>>;


#ifdef LOCAL
#include "./debug.hpp"
#else
#define debug(...)
#define print_line
#endif

using std::cout;
