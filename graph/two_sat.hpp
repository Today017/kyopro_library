#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/graph/scc.hpp"

/// @brief 2-SAT
struct TwoSat{
    TwoSat(int n){ g=VVI(2*n); }

    /// @brief 条件 `i==fi || j==fj` を追加
    void add(int i, bool fi, int j, bool fj){
        // 2i = i が true, 2i+1 = i が false
        i=2*i+!fi,j=2*j+!fj;
        // !i -> j, !j -> i
        g[i^1].push_back(j),g[j^1].push_back(i);
    }

    /// @brief 2-SATを解く
    /// @brief 解が存在しないなら空のvectorを返す
    vector<bool> solve(){
        auto [mem,ng,gr]=SccDecomposition(g);
        int n=g.size()/2;
        vector<bool> ret(n);

        REP(i,n){
            if(gr[i*2]==gr[i*2+1]) return vector<bool>();
            // 2i(true) が後ろなら i は true
            ret[i]=gr[i*2]>gr[i*2+1];
        }

        return ret;
    }

private:
    VVI g;
};