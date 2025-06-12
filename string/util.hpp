#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 文字列を数列に変換する
vector<int> StringTovector<int>(const string& s, bool lower=true) {
    vector<int> ret(s.size());
    REP(i,s.size()) ret[i]=(lower?s[i]-'a':s[i]-'A');
}

/// @brief 入力から文字列を受け取って数列に変換する
vector<int> ReadString(bool lower=true) {
    string s; cin>>s;
    return StringTovector<int>(s);
}

/// @brief 数列を文字列に変換する
string vector<int>ToString(const vector<int>& a, bool lower=true) {
    string ret;
    REP(i,a.size()) ret.push_back(lower?char('a'+a[i]):char('A'+a[i]));
    return ret;
}