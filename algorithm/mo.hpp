#include"../../kyopro_library/template.hpp"

///@brief Mo's Algorithm
///@ref https://ei1333.hateblo.jp/entry/2017/09/11/211011
struct Mo {
    ///@brief コンストラクタ
    Mo(int n): n(n), q(0) {}

    ///@brief クエリ [l, r) を追加する
    void add(int l, int r) {
        q++;
        ls.push_back(l);
        rs.push_back(r);
    }

    ///@brief クエリを実行する
    ///@param add_left `add_left(i)` i 番目の要素が左から加わるときの処理
    ///@param add_right `add_right(i)` i 番目の要素が右から加わるときの処理
    ///@param del_left `del_left(i)` i 番目の要素が左から抜けるときの処理
    ///@param del_right `del_right(i)` i 番目の要素が右から抜けるときの処理
    ///@param out `out(i)` i 番目のクエリの答えを求めたときの処理
    ///@note O(N sqrt(Q))
    template<typename F1, typename F2, typename F3, typename F4, typename F5>
    void execute(F1&& add_left, F2&& add_right, F3&& del_left, F4&& del_right, F5&& out) {
        vector<int> qi(q); iota(all(qi),0);

        // https://nyaannyaan.github.io/library/misc/mo.hpp.html
        const int wid=max<int>(1,1.0*n/max<double>(1.0,sqrt(q*2.0/3.0)));
        sort(all(qi),[&](int a, int b) {
            if(ls[a]/wid!=ls[b]/wid) return ls[a]<ls[b];
            if((ls[a]/wid)&1) return rs[a]<rs[b];
            return rs[a]>rs[b];
        });

        int nl=0, nr=0;
        for(int& i: qi){
            while(nl>ls[i]) add_left(--nl);
            while(nr<rs[i]) add_right(nr++);
            while(nl<ls[i]) del_left(nl++);
            while(nr>rs[i]) del_right(--nr);
            out(i);
        }
    }

private:
    int n, q;
    vector<int> ls, rs;
};