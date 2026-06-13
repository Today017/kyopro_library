#pragma once

#include"../../kyopro_library/base/include.hpp"
#include"../../kyopro_library/base/type.hpp"

const char NL='\n';
void flush() { cout.flush(); }

inline string YesNo(bool f) { return f? "Yes": "No"; }
inline string YESNO(bool f) { return f? "YES": "NO"; }

template<typename T>
istream& operator>>(istream& is, vector<vector<T>>& v) {
    for(auto& x: v) for(auto& y: x) is>>y;
    return is;
}
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x: v) is>>x;
    return is;
}
template<typename T1, typename T2>
istream& operator>>(istream& is, pair<T1,T2>& p) {
    is>>p.first>>p.second;
    return is;
}

template<class... T> void input(T&... a) { (cin>>...>>a); }

template<class T> void input_index(T& a) { a--; }
template<class T, class... Ts> void input_index(T& a, Ts&... b) { a--; input_index(b...); }

#ifndef DEBUG
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& p) {
    os<<p.fi<<' '<<p.se;
    return os;
}
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const PR<T1,T2>& p) {
    os<<p.fi<<' '<<p.se;
    return os;
}
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3>& t) {
    os<<' '<<get<0>(t)<<' '<<get<1>(t)<<' '<<get<2>(t);
    return os;
}
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, const TR<T1,T2,T3>& t) {
    os<<' '<<get<0>(t)<<' '<<get<1>(t)<<' '<<get<2>(t);
    return os;
}
template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3,T4>& t) {
    os<<' '<<get<0>(t)<<' '<<get<1>(t)<<' '<<get<2>(t)<<' '<<get<3>(t);
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<vector<T>>>& a) {
    int I=a.size();
    for(int i=0; i<I; i++) {
        int J=a[i].size();
        for(int j=0; j<J; j++) {
            int K=a[i][j].size();
            for(int k=0; k<K; k++) {
                os<<a[i][j][k];
                if(k!=K-1) os<<' ';
            }
            os<<NL;
        }
        os<<NL;
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& a) {
    int I=a.size();
    for(int i=0; i<I; i++) {
        int J=a[i].size();
        for(int j=0; j<J; j++) {
            os<<a[i][j];
            if(j!=J-1) os<<' ';
        }
        cout<<NL;
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& a) {
    int n=a.size();
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& a) {
    for(auto itr=a.begin(); itr!=a.end(); itr++) {
        os<<*itr;
        if(next(itr)!=a.end()) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& a) {
    for(auto itr=a.begin(); itr!=a.end(); itr++) {
        os<<*itr;
        if(next(itr)!=a.end()) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const deque<T>& a) {
    for(auto itr=a.begin(); itr!=a.end(); itr++) {
        os<<*itr;
        if(next(itr)!=a.end()) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, queue<T> a) {
    while(!a.empty()) {
        os<<a.front();
        a.pop();
        if(a.size()) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T> a) {
    while(!a.empty()) {
        os<<a.top();
        a.pop();
        if(a.size()) os<<' ';
    }
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T,vector<T>,greater<T>> a) {
    while(!a.empty()) {
        os<<a.top();
        a.pop();
        if(a.size()) os<<' ';
    }
    return os;
}
template<typename T, auto N>
ostream& operator<<(ostream& os, array<T,N> a) {
    for(int i=0; i<N; i++) {
        os<<a[i];
        if(i!=N-1) os<<' ';
    }
    return os;
}
#endif

template<class T, class... Ts>
void put(const T& a, const Ts&... b) {
    cout<<a;
    (cout<<...<<(cout<<"", b));
    cout<<' ';
}

template<class T, class... Ts>
void line(const T& a, const Ts&... b) {
    cout<<a;
    (cout<<...<<(cout<<' ', b));
    cout<<' ';
}

void say() { cout<<'\n'; }
template<class T, class... Ts>
void say(const T& a, const Ts&... b) {
    cout<<a;
    (cout<<...<<(cout<<' ', b));
    cout<<'\n';
}

#define O(...) { say(__VA_ARGS__); return; }