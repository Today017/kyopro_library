#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/string/suffix_array.hpp"

///@brief LCP Array
///@brief `lcp[i] := sa[i] と sa[i-1] の lcp の長さ`
///@ref https://qiita.com/kgoto/items/9e28e37b8a4b15ea7230
vi LcpArray(const string &s, const vi& sa) {
    int n=s.size();
    vi lcp(n-1),rank(n);
    rep(i,n) rank[sa[i]]=i;

    int len=0;//lcp の長さ
    rep(i,n) {
        if(rank[i]==0) continue;
        int j=sa[rank[i]-1];

        while(i+len<n && j+len<n && s[i+len]==s[j+len]) len++;
        lcp[rank[i]-1]=len;

        if(len>0) len--;
    }

    return lcp;
}

vi LcpArray(vi s) {
    auto sa=SuffixArray(s);
    int n=s.size();
    vi lcp(n-1),rank(n);
    rep(i,n) rank[sa[i]]=i;

    int len=0;//lcp の長さ
    rep(i,n) {
        if(rank[i]==0) continue;
        int j=sa[rank[i]-1];

        while(i+len<n && j+len<n && s[i+len]==s[j+len]) len++;
        lcp[rank[i]-1]=len;

        if(len>0) len--;
    }

    return lcp;
}
