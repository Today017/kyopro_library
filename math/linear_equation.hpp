#include"../../kyopro_library/template.hpp"

/// @brief F_2 上の連立線形方程式
/// @ref https://mathlandscape.com/solution-sp/
/// @ref https://yukicoder.me/submissions/1011997
/// @ref verify: https://yukicoder.me/problems/no/2895
/// @ref verify: https://yukicoder.me/problems/no/3229
/// @ref verify: https://judge.yosupo.jp/problem/system_of_linear_equations_mod_2

/// @brief 掃き出し法
/// @param a 連立方程式 Ax=b の拡大係数行列
/// @param col 拡大係数行列の列数
/// @param where ピボットとなる変数を記録するための配列
/// @return A のランク
template<int MAX_COL>
int RowReduction(vector<bitset<MAX_COL>>& a, int col, vector<int>& where) {
    int row=a.size();
    int rank=0;
    for(int c=0; c<col-1; c++) {
        int pivot=rank;
        while(pivot<row && !a[pivot][c]) pivot++;
        if(pivot==row) continue;
        swap(a[pivot],a[rank]);
        where.push_back(c);
        for(int r=0; r<row; r++) {
            if(r!=rank && a[r][c]) a[r]^=a[rank];
        }
        rank++;
    }
    return rank;
}

/// @brief 連立線形方程式 Ax=b を解く
/// @param col 連立方程式の変数の数
/// @param x0 特殊解(b=0 の場合は自明解になる)
/// @param ker Ax=0 の解空間の基底
/// @param ONE_KER 基底のサイズが巨大な場合、基底を1つだけ求められれば良いときはtrue
/// @note 一般解は x0 と解空間の基底の任意の線形結合で表される
/// @attention A のサイズによっては基底のサイズが巨大になるので注意すること
template<int MAX_COL, bool ONE_KER=false>
int LinearEquation(vector<bitset<MAX_COL>> a, vector<bool> b, int col, vector<bool>& x0, vector<vector<bool>>& ker) {
    int row=a.size();
    assert(b.size()==row);

    vector<bitset<MAX_COL>> a2(row);
    for(int i=0; i<row; i++) {
        a2[i].reset();
        for(int j=0; j<col; j++) a2[i][j]=a[i][j];
        if(b[i]) a2[i][col]=true;
    }

    vector<int> where;
    int rank=RowReduction<MAX_COL>(a2,col+1,where);

    for(int r=rank; r<row; r++) if(a2[r][col]) return false;

    x0=vector<bool>(col,false);
    for(int i=0; i<rank; i++) x0[where[i]]=a2[i][col];

    int r=0;
    for(int c=0; c<col; c++) {
        if(r<rank && c==where[r]) {
            r++;
            continue;
        }
        vector<bool> x(col);
        x[c]=true;
        for(int r2=0; r2<r; r2++) x[where[r2]]=a2[r2][c];
        ker.push_back(x);

        if (ONE_KER) return true;
    }

    return true;
}
