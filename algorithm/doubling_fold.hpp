#include"../../kyopro_library/template.hpp"

///@brief ダブリング（モノイド合成）
///@tparam Monoid 合成するモノイド
///@tparam Log ダブリングの深さ
template<typename Monoid, int Log>
struct DoublingFold {
    using Type=typename Monoid::Type;
    DoublingFold()=default;

    ///@brief コンストラクタ
    ///@param p 各頂点の遷移先
    ///@param v 各頂点の値
    ///@note O(N Log)
    DoublingFold(const vector<int>& p, const vector<Type>& v) {
        int n=p.size();
        dat=vector<vector<Type>>(Log+1,vector<Type>(n,Monoid::id()));
        nxt=vector<vector<int>>(Log+1,vector<int>(n));
        rep(i,n) dat[0][i]=v[i], nxt[0][i]=p[i];
        rep(i,Log) rep(j,n) {
            nxt[i+1][j]=nxt[i][nxt[i][j]];
            dat[i+1][j]=Monoid::op(dat[i][j],dat[i][nxt[i][j]]);
        }
    }

    ///@brief (遷移先, モノイド積) を返す
    ///@brief 頂点 start から k 回遷移したときの頂点とモノイド積の組を返す
    ///@note O(Log)
    pair<int, Type> fold(int start, ll k) {
        Type ret= Monoid::id();
        rep(b,Log+1) if(k>>b&1) {
            ret=Monoid::op(ret,dat[b][start]);
            start=nxt[b][start];
        }
        return {start, ret};
    }

private:
    vector<vector<Type>> dat;
    vector<vector<int>> nxt;
};