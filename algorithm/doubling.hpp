#include"../../kyopro_library/template.hpp"

///@brief ダブリング
///@param Log ダブリングの深さ
template<int Log>
struct Doubling {
    Doubling()=default;

    ///@brief コンストラクタ
    ///@param v 各頂点からの遷移先
    ///@note O(N Log)
    Doubling(const vector<int>& v) {
        int n=v.size();
        nxt=vector<vector<int>>(Log+1,vector<int>(n));
        rep(i,n) nxt[0][i]=v[i];
        rep(i,Log) rep(j,n) nxt[i+1][j]=nxt[i][nxt[i][j]];
    }

    ///@brief 頂点 start から k 回遷移した先の頂点を返す
    ///@note O(Log)
    int next(int start, ll k) {
        rep(b,Log+1) if(k>>b&1) start=nxt[b][start];
        return start;
    }

private:
    vector<vector<int>> nxt;
};