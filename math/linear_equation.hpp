#include"../../kyopro_library/template.hpp"

/// @brief F_2 上の連立線形方程式
/// @ref https://mathlandscape.com/solution-sp/
/// @ref https://yukicoder.me/submissions/1011997
/// @ref verify:https://yukicoder.me/problems/no/2895

/// @brief 掃き出し法
/// @param a 連立方程式 Ax=b の拡大係数行列
/// @param where ピボットとなる変数を記録するための配列
/// @return A のランク
int RowReduction(vector<vector<bool>>& a, VI& where) {
    int row=a.size(),col=a.front().size();
    int rank=0;
    REP(c,col-1) {
        int pivot=rank;
        while(pivot<row&&!a[pivot][c]) pivot++;
        if(pivot==row) continue;
        swap(a[pivot],a[rank]);
        where.push_back(c);
        REP(r,row) {
            if(r!=rank&&a[r][c]) {
                //A[r]^=A[c]
                REP(i,col) a[r][i]=a[r][i]^a[rank][i];
            }
        }
        rank++;
    }
    return rank;
}

/// @brief 連立線形方程式 Ax=b を解く
/// @param x0 特殊解(b=0 の場合は自明解になる)
/// @param ker Ax=0 の解空間の基底
/// @note 一般解は x0 と解空間の基底の任意の線形結合で表される
/// @attention A のサイズによっては基底のサイズが巨大になるので注意すること
bool LinearEquation(vector<vector<bool>> a, vector<bool> b, vector<bool>& x0, vector<vector<bool>>& ker) {
    int row=a.size(),col=a.front().size();
    assert(b.size()==row);
    vector<vector<bool>> a2=a;
    REP(i,row) a2[i].push_back(b[i]);

    VI where;
    int rank=RowReduction(a2,where);

    for(int r=rank; r<row; r++) if(a2[r].back()) return false;

    x0=vector<bool>(col,false);
    REP(i,rank) x0[where[i]]=a2[i].back();

    int r=0;
    REP(c,col) {
        if(r<rank&&c==where[r]) {
            r++;
            continue;
        }
        vector<bool> x(col);
        x[c]=true;
        REP(r2,r) x[where[r2]]=a2[r2][c];
        ker.push_back(x);
    }

    return true;
}