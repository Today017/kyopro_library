#pragma once
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<n; i++)
#define per(i,n) for(int i=(n)-1; i>=0; i--)
#define all(x) (x).begin(), (x).end()
bool chmax(auto& a, auto b) { return a<b ? a=b, 1: 0; }
bool chmin(auto& a, auto b) { return a>b ? a=b, 1: 0; }
using ll=long long; const int INF=1e9+10; const ll INFL=4e18;

#ifdef DEBUG
#include "./debug.hpp"
#else
#define debug(...)
#define print_line
#endif
