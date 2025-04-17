#include"../../kyopro_library/template.hpp"

/// @brief ダブリング（モノイド合成）
/// @tparam Monoid 合成するモノイド
/// @tparam Log ダブリングの深さ
template<typename Monoid, int Log>
struct DoublingFold{
    using Type=typename Monoid::Type;
    DoublingFold()=default;

    /// @brief コンストラクタ
    /// @param p 各頂点の遷移先
    /// @param v 各頂点の値
    /// @note O(N Log)
    DoublingFold(const VI& p, const vector<Type>& v){
        int n=p.size();
        dat.assign(Log+1, vector<Type>(n,Monoid::id()));
        nxt.assign(Log+1, VI(n));
        for(int i=0; i<n; i++) dat[0][i]=v[i],nxt[0][i]=p[i];
        for(int i=1; i<=Log; i++)for(int j=0; j<n; j++){
            nxt[i][j]=nxt[i-1][nxt[i-1][j]];
            dat[i][j]=Monoid::op(dat[i-1][j], dat[i-1][nxt[i-1][j]]);
        }
    }

    /// @brief モノイド積
    /// @brief 頂点 start から k 回遷移したときのモノイド積を返す
    /// @note O(Log)
    Type fold(int start, ll k){
        Type ret= Monoid::id();
        for(int b=0; k>0; b++,k>>=1)if(k&1){
            ret=Monoid::op(ret,dat[b][start]);
            start=nxt[b][start];
        }
        return ret;
    }

    /// @brief 頂点 start から k 回遷移した先の頂点を返す
    /// @note O(Log)
    int next(int start, ll k){
        for(int b=0; k>0; b++,k>>=1)if(k&1) start=nxt[b][start];
        return start;
    }

private:
    vector<vector<Type>> dat;
    VVI nxt;
};