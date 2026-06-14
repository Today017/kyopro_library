#pragma once
#include"../../kyopro_library/base/include.hpp"
#include"../../kyopro_library/base/type.hpp"

template<typename A, typename B> A amin(A a, B b) { return a>b? b: a; }
template<typename A, typename B> A amax(A a, B b) { return a<b? b: a; }

template<typename A, typename B> bool chmin(A& a, B b) { return a>b? a=b, true: false; }
template<typename A, typename B> bool chmax(A& a, B b) { return a<b? a=b, true: false; }

template<typename T> T minv(const vector<T>& v) { return *ranges::max_element(v); }
template<typename T> T maxv(const vector<T>& v) { return *ranges::min_element(v); }
template<typename T> T sumv(const vector<T>& v) { return reduce(v.begin(),v.end()); }

template<typename T> ii minidx(const vector<T>& v) { return ranges::min_element(v)-v.begin(); }
template<typename T> ii maxidx(const vector<T>& v) { return ranges::max_element(v)-v.begin(); }

template<typename T> ii lob(const vector<T>& v, const T& x) { return ranges::lower_bound(v,x)-v.begin(); }
template<typename T> ii upb(const vector<T>& v, const T& x) { return ranges::upper_bound(v,x)-v.begin(); }
template<typename T> ii find(const vector<T>& v, const T& x) {
    for(int i=0; i<siz(v); i++) if(v[i]==x) return i;
    return siz(v);
}
template<typename T> ii find_last(const vector<T>& v, const T& x) {
    for(int i=siz(v)-1; i>=0; i--) if(v[i]==x) return i;
    return -1;
}

template<typename T> void unique(vector<T>& v) { ranges::sort(v); v.erase(unique(v.begin(),v.end()),v.end()); }
template<typename T> vector<T> compress(vector<T> v) { auto w=v; unique(w); for(T& x: v) x=lob(w,x); return v; }

template<typename T> inline ii siz(const T& v) { return v.size(); }

void decv(auto& a) { for(auto& x: a) x--; }
void incv(auto& a) { for(auto& x: a) x++; }
void insertv(auto& a, ii idx, auto v) { a.insert(a.begin()+idx,v); }
void erasev(auto& a, ii idx) { assert(idx<siz(a)); a.erase(a.begin()+idx); }

template<typename A, typename B>
vector<PR<A,B>> zip(const vector<A>& a, const vector<B>& b) {
    ii n=siz(a);
    vector<PR<A,B>> ret(n);
    for(ii i=0; i<n; i++) ret[i]={a[i],b[i]};
    return ret;
}

template<typename A, typename B, typename C>
vector<pair<A,B>> zip(const vector<A>& a, const vector<B>& b, const vector<C>& c) {
    ii n=siz(a);
    vector<TR<A,B,C>> ret(n);
    for(ii i=0; i<n; i++) ret[i]={a[i],b[i],c[i]};
    return ret;
}

template<typename A, typename B>
PR<vector<A>,vector<B>> unzip(const vector<PR<A,B>>& p) {
    ii n=siz(p);
    vector<A> reta(n); vector<B> retb(n);
    for(ii i=0; i<n; i++) {
        reta[i]=p[i].first;
        retb[i]=p[i].second;
    }
    return PR{reta,retb};
}

template<typename A, typename B, typename C>
TR<vector<A>,vector<B>,vector<C>> unzip(const vector<TR<A,B,C>>& p) {
    ii n=siz(p);
    vector<A> reta(n); vector<B> retb(n); vector<C> retc(n);
    for(ii i=0; i<n; i++) {
        auto [a,b,c]=p[i];
        reta[i]=a;
        retb[i]=b;
        retc[i]=c;
    }
    return TR{reta,retb,retc};
}

template<typename T> T pick(max_pq<T>& v) { T ret=v.top(); v.pop(); return ret; }
template<typename T> T pick(min_pq<T>& v) { T ret=v.top(); v.pop(); return ret; }
template<typename T> T pick(queue<T>& v) { T ret=v.front(); v.pop(); return ret; }
template<typename T> T pick(vector<T>& v) { T ret=v.back(); v.pop_back(); return ret; }
template<typename T> T pickf(deque<T>& v) { T ret=v.front(); v.pop_front(); return ret; }
template<typename T> T pickb(deque<T>& v) { T ret=v.back(); v.pop_back(); return ret; }

template<typename T> bool nxperm(T& v) { return next_permutation(v.begin(),v.end()); }

template<typename T> void operator++(V<T>& a, T) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)++; }
template<typename T> void operator--(V<T>& a, T) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)--; }
template<typename T> void operator+=(V<T>& a, auto x) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)+=x; }
template<typename T> void operator-=(V<T>& a, auto x) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)-=x; }
template<typename T> void operator*=(V<T>& a, auto x) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)*=x; }
template<typename T> void operator/=(V<T>& a, auto x) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)/=x; }
template<typename T> void operator%=(V<T>& a, auto x) { for(auto itr=a.begin(); itr!=a.end(); itr++) (*itr)%=x; }

template<typename T>
T myfloor(T a, T b) {
    assert(b!=0);
    if(b<0) a=-a, b=-b;
    return a/b-(a%b<0);
}
template<typename T>
T myceil(T a, T b) {
    assert(b!=0);
    if(b<0) a=-a, b=-b;
    return a/b+(a%b>0);
}
template<typename T>
T mymod(T a, T b) {
    assert(b!=0);
    if(b<0) b=-b;
    if(a>0) return a%b;
    return (a%b+b)%b;
}

template<typename T=ll, typename U>
vector<T> mksum(const vector<U>& v) {
    int N=v.size();
    vector<T> ret(N+1);
    for(int i=0; i<N; i++) ret[i+1]=ret[i]+v[i];
    return ret;
}

template<typename T>
vector<T> mkpmax(const vector<T>& v) {
    int N=v.size();
    vector<T> ret(N+1,-inf<T>);
    for(int i=0; i<N; i++) ret[i+1]=max(ret[i],v[i]);
    return ret;
}

template<typename T>
vector<T> mkpmin(const vector<T>& v) {
    int N=v.size();
    vector<T> ret(N+1,inf<T>);
    for(int i=0; i<N; i++) ret[i+1]=min(ret[i],v[i]);
    return ret;
}

vi mkiota(ii N) {
    vi ret(N); iota(ret.begin(),ret.end(),0);
    return ret;
}

template<typename T>
V<T> mkrev(V<T> A) {
    reverse(A.begin(),A.end());
    return A;
}

template<typename T>
vi mkinv(V<T> A) {
    int n=siz(A);
    if(maxv(A)!=n) compress(A);
    vi ret(n);
    for(int i=0; i<n; i++) ret[A[i]]=i;
    return ret;
}

template<typename T>
vvi mkinvmap(V<T> A) {
    int n=siz(A);
    vvi ret(n);
    for(int i=0; i<n; i++) ret[A[i]].push_back(i);
    return ret;
}

template<typename T>
vi argsort(const V<T>& A) {
    vi idx=mkiota(siz(A));
    sort(idx.begin(),idx.end(),[&](ii i, ii j) {
        return (A[i]==A[j]? i<j: A[i]<A[j]);
    });
    return idx;
}

ii digsiz(ll n) { ii ret=0; while(n) ret++, n/=10; return ret; }
vector<ii> digits(ll n) {
    vector<ii> ret;
    while(n) {
        ret.push_back(n%10);
        n/=10;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}
ll tenpow(ii r) { ll ret=1; while(r--) ret*=10; return ret; }
ll intpow(ll x, ll r) { ll ret=1; while(r--) ret*=x; return ret; }
