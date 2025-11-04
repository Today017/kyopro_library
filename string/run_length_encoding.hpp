#include"../../kyopro_library/template.hpp"

/// @brief 配列sをランレングス圧縮する
template<typename T>
vector<pair<T,int>> RunLenghtEncoding(const vector<T>& s) {
    int n=s.size();
    vector<pair<T,int>> ret;
    for(int i=0; i<n; i++) {
        if(ret.empty() || ret.back().first!=s[i]) ret.push_back({s[i],1});
        else ret.back().second++;
    }
    return ret;
}

/// @brief 文字列sをランレングス圧縮する
vector<pair<char,int>> RunLengthEncoding(const string& s) {
    return RunLenghtEncoding(vector<char>(s.begin(),s.end()));
}