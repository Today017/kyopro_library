#include"../../../kyopro_library/template.hpp"
#include"../../../kyopro_library/graph/flow/max_flow.hpp"

///@brief 燃やす埋める
struct MoyasuUmeru {
    MoyasuUmeru(int n) {
        this->n=n;
        start=n;
        goal=n+1;
        mf=MaxFlow(n+2);
    }

    ///@brief x[i] = 0 のときコスト zero, x[i] = 1 のときコスト one がかかるという条件を追加する
    void add_single(int i, ll zero, ll one) {
        if(zero<=one) {
            //基本コストがzeroで、iを0から1に変えると+one-zeroされる
            offset+=zero;
            mf.add_edge(start,i,one-zero);
        } else {
            //基本コストがoneで、iを1から0に変えると-one+zeroされる
            offset+=one;
            mf.add_edge(i,goal,zero-one);
        }
    }

    /**
     * @brief
     * x[ i ], x[ j ] の組み合わせについて、以下のコストかかるという条件を追加する
     * |          | x[j] = 0 | x[j] = 1 |
     * | ---      | ---      | ---      |
     * | x[i] = 0 | a        | b        |
     * | x[i] = 1 | c        | d        |
     * 
     * @attention b + c >= a + d を要求する
    */
    void add_double(int i, int j, ll a, ll b, ll c, ll d) {
        assert(b+c>=a+d);
        offset+=a;
        add_single(i,0,c-a);
        add_single(j,0,d-c);
        mf.add_edge(i,j,b+c-a-d);
    }

    ///@brief 解を復元する
    ///@attention `solve()` を実行した後に使うこと
    vector<int> fukugen() {
        auto ret=mf.mincut(start);
        ret.pop_back(); ret.pop_back();
        for(int& x: ret) x^=1;
        return ret;
    }

    ///@brief コスト最小値を求める
    ll solve() { return mf.flow(start,goal)+offset; }

private:
    int n,start,goal;
    ll offset=0;
    MaxFlow mf;
};
