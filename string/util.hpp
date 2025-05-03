#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 文字列を数列に変換する
VI StringToVi(const string& s, bool lower=true) {
    VI ret(s.size());
    REP(i,s.size()) ret[i]=(lower?s[i]-'a':s[i]-'A');
}

/// @brief 入力から文字列を受け取って数列に変換する
VI ReadString(bool lower=true) {
    string s; cin>>s;
    return StringToVi(s);
}

/// @brief 数列を文字列に変換する
string ViToString(const VI& a, bool lower=true) {
    string ret;
    REP(i,a.size()) ret.push_back(lower?char('a'+a[i]):char('A'+a[i]));
    return ret;
}