#include"../../kyopro_library/template.hpp"

/// @brief スパーステーブル
/// @tparam Band 冪等な半群
template<typename Band>
struct SparseTable{
    using Type=typename Band::Type;
    SparseTable()=default;

    /// @brief 配列 v からスパーステーブルを構築する
    /// @note O(N log(N))
    SparseTable(const vector<Type>&v) {
        n=v.size();
        dat.assign(__lg(n)+1,vector<Type>(n));
        dat[0]=v;
        for(int i=1;i<(int)dat.size();i++) {
            for(int j=0;j+(1<<i)<=n;j++) {
                dat[i][j]=Band::op(dat[i-1][j],dat[i-1][j+(1<<(i-1))]);
            }
        }
    }

    /// @brief 区間 [l, r) の半群積を返す
    Type fold(int l,int r) {
        r--;
        int i=__lg(r-l+1);
        return Band::op(dat[i][l],dat[i][r-(1<<i)+1]);
    }

    int size() {return n;}
    Type operator[](int i)const{return fold(i,i+1);}

private:
    int n;
    vector<vector<Type>>dat;
};