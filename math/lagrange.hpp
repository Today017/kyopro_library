#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/multipoint_evaluate.hpp"

///@brief ラグランジュ補間
///@brief n+1 個の点 (x[i], y[i]) を通る n 次多項式の係数を返す
///@note O(n (log(n))^2)
template<typename T>
vector<T> LagrangePolynomial(vector<T> x, vector<T> y){
    int n=x.size();
    int n2=1;
    while(n2<n) n2<<=1;

    vector<vector<T>> g(n2*2,{1});
    rep(i,n) g[n2+i]={-x[i],1};
    for(ll i=n2-1; i>0; i--) g[i]=Fps::Mul(g[i<<1],g[i<<1|1]);

    vector<T> prod=g[1];
    vector<T> diff=Fps::Differential(prod), eval=MultipointEvaluate(diff,x);

    using P=pair<vector<T>,vector<T>>;//first/second
    vector<P> g2(n2*2,{{0},{1}});
    rep(i,n) g2[n2+i]={{y[i]},{-eval[i]*x[i],eval[i]}};
    auto merge=[](P l, P r)-> P {
        vector<T> tmp1=Fps::Mul(l.first,r.second),tmp2=Fps::Mul(l.second,r.first);
        return {Fps::Add(tmp1,tmp2),Fps::Mul(l.second,r.second)};
    };
    for(ll i=n2-1; i>0; i--) g2[i]=merge(g2[i<<1],g2[i<<1|1]);

    vector<T> ret=g2[1].first;
    T p=1; rep(i,n) p*=eval[i]; p=p.inv();
    rep(i,n) ret[i]*=p;
    return ret;
}