#include"../../kyopro_library/template.hpp"

///@brief 配列sをランレングス圧縮する
template<typename T>
vector<pair<T,int>> RunLengthEncoding(const vector<T>& s) {
    int n=s.size();
    vector<pair<T,int>> ret;
    rep(i,n) {
        if(ret.empty() || ret.back().first!=s[i]) ret.push_back({s[i],1});
        else ret.back().second++;
    }
    return ret;
}

///@brief 文字列sをランレングス圧縮する
vector<pair<char,int>> RunLengthEncoding(const string& s) {
    return RunLengthEncoding(vector<char>(all(s)));
}
