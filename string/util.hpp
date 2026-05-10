#pragma once
#include"../../kyopro_library/template.hpp"

///@brief 文字列を数列に変換する
vector<int> StringToVi(const string& s, char base='a') {
    vector<int> ret(s.size());
    rep(i,s.size()) ret[i]=s[i]-base;
    return ret;
}

///@brief 入力から文字列を受け取って数列に変換する
vector<int> ReadString(char base='a') {
    string s; cin>>s;
    return StringToVi(s,base);
}

///@brief 数列を文字列に変換する
string ViToString(const vector<int>& a, char base='a') {
    string ret;
    rep(i,a.size()) ret.push_back(char(base+a[i]));
    return ret;
}

vector<vector<int>> NextIndex(const vector<int>& a, char base='a', int C=26) {
    //部分列DPとかで使うアレ
    int N=a.size();
    vector<vector<int>> ret(N+1,vector<int>(C,N));
    per(i,N) {
        rep(j,C) ret[i][j]=ret[i+1][j];
        ret[i][a[i]]=i;
    }
    return ret;
}
