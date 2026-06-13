#pragma once
#include"../../kyopro_library/template.hpp"

///@brief ダブリング
///@param Log ダブリングの深さ
template<int Log>
struct Doubling {
    Doubling()=default;

    ///@brief コンストラクタ
    ///@param V 各頂点からの遷移先
    ///@note O(N Log)
    Doubling(const vi& V) {
        int n=V.size();
        nxt=vector<vi>(Log+1,vi(n));
        rep(i,n) nxt[0][i]=V[i];
        rep(i,Log) rep(j,n) nxt[i+1][j]=nxt[i][nxt[i][j]];
    }

    ///@brief 頂点 start から K 回遷移した先の頂点を返す
    ///@note O(Log)
    int next(int start, ll K) {
        rep(b,Log+1) if(K>>b&1) start=nxt[b][start];
        return start;
    }

private:
    vector<vi> nxt;
};