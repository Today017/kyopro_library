#include"../../kyopro_library/template.hpp"

/// @brief ダブリング
/// @param Log ダブリングの深さ
template<int Log>
struct Doubling {
    Doubling()=default;

    /// @brief コンストラクタ
    /// @param v 各頂点からの遷移先
    /// @note O(N Log)
    Doubling(const VI& v) {
        int n=v.size();
        nxt.assign(Log+1,VI(n));
        REP(i,n) nxt[0][i]=v[i];
        REP(i,Log) REP(j,n) nxt[i+1][j]=nxt[i][nxt[i][j]];
    }

    /// @brief 頂点 start から k 回遷移した先の頂点を返す
    /// @note O(Log)
    int next(int start, ll k) {
        for(int b=0; k>0; b++,k>>=1) if(k&1) start=nxt[b][start];
        return start;
    }

private:
    VVI nxt;
};