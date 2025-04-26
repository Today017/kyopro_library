#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief Suffix Array
/// @brief `sa[i] = j <-> s[j:] が辞書順 i 番目`
/// @brief O(n log(n))
/// @ref https://wk1080id.hatenablog.com/entry/2018/12/25/005926
template<int C=256>
VI suffixArray(string s) {
    s.push_back('$');
    int n=s.size();
    VI p(n), c(n), cnt(max(n,C),0);
    //p[i] := 辞書順 i 番目のインデックス
    //c[i] := インデックス i の部分文字列の同値類

    //2^0,2^1,...,2^k,... をやる
    //k=0
    REP(i,n) cnt[s[i]]++;
    FOR(i,1,cnt.size()) cnt[i]+=cnt[i-1];
    //辞書順 = 累積和の小さい順 になる
    REP(i,n) p[--cnt[s[i]]]=i;
    //同値類を計算する
    c[p[0]]=0;
    FOR(i,1,n) {
        c[p[i]]=c[p[i-1]];
        if(s[p[i]]!=s[p[i-1]]) c[p[i]]++;
    }

    VI np(n),nc(n);
    for(int k=0; (1<<k)<n; k++) {
        //k を使って、(c[i],c[i+2^k]) でソート、 p[i]-=2^k でできる
        //c[i+2^k] でソート
        REP(i,n) np[i]=p[i]-(1<<k),(np[i]+=n)%=n;
        fill(ALL(cnt),0);
        REP(i,n) cnt[c[np[i]]]++;
        FOR(i,1,cnt.size()) cnt[i]+=cnt[i-1];
        FOR(i,n-1,-1) p[--cnt[c[np[i]]]]=np[i];
        //同値類
        nc[p[0]]=0;
        FOR(i,1,n) {
            nc[p[i]]=nc[p[i-1]];
            if(c[p[i]]!=c[p[i-1]] || c[(p[i]+(1<<k))%n]!=c[(p[i-1]+(1<<k))%n]) nc[p[i]]++;
        }
        swap(c,nc);
    }

    p.erase(p.begin());
    return p;
}