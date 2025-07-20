#pragma once
#include <bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()
#define REP(i, n) for(ll i=0; i<(ll)(n); i++)

template<typename T> bool chmax(T& a, T b) { return a<b ? a=b, true : false; }
template<typename T> bool chmin(T& a, T b) { return a>b ? a=b, true : false; }
using ll=long long; const int INF=1e9+10; const ll INFL=4e18;

#ifdef LOCAL
#include "./debug.hpp"
#else
#define debug(...)
#define print_line
#endif

