#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/fps.hpp"

/// @brief n 次多項式 f について、n 個の点 x[i] における f(x[i]) を返す
/// @note O(n (log(n))^2)
template<typename T>
vector<T> MultipointEvaluate(vector<T> f, vector<T> x) {
    int n=x.size();
    if(n==0) return{};
    if(n==1) {
        T ret=0,tmp=1;
        for(T a:f) ret+=a*tmp,tmp*=x[0];
        return {ret};
    }
    int n2=1;
    while(n2<n) n2<<=1;
    vector<vector<T>> g(n2*2,{1});
    REP(i,n) g[n2+i]={-x[i],1};
    FOR(i,n2-1,0) g[i]=PolyMul(g[i<<1],g[i<<1|1]);

    g[1]=PolyDiv(f,g[1]).second;
    FOR(i,2,n2+n) g[i]=PolyDiv(g[i>>1],g[i]).second;
    vector<T> ret(n);
    REP(i,n) ret[i]=g[n2+i][0];
    return ret;
}