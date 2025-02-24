#include"../../kyopro_library/template.hpp"

// 倍数高速ゼータ変換
// v'[k] = Σ_{k|d} v[d] なる v' を返す。
// O(|v| log(log(|v|)))
template<typename Monoid>
vector<typename Monoid::Type>zetaMultiple(vector<typename Monoid::Type>v){
    int n=v.size()-1;
    auto prime=primeEnumerate(n);
    for(int p:prime)for(int k=n/p;k>0;k--)v[k]=Monoid::op(v[k],v[k*p]);
    return v;
}

// 約数高速ゼータ変換
// v'[k] = Σ_{d|k} v[d] なる v' を返す。
// O(|v| log(log(|v|)))
template<typename Monoid>
vector<typename Monoid::Type>zetaDivisor(vector<typename Monoid::Type>v){
    int n=v.size()-1;
    auto prime=primeEnumerate(n);
    for(int p:prime)for(int k=1;k*p<=n;k++)v[k*p]=Monoid::op(v[k*p],v[k]);
    return v;
}

// 約数高速メビウス変換
// v'[k] = Σ_{d|k} μ(d) v[k/d] なる v' を返す。
// 逆変換が必要なので、v は可換群の元である必要がある。
// O(|v| log(log(|v|)))
template<typename Abel>
vector<Abel>mobiusDivisor(vector<Abel>v){
    int n=v.size()-1;
    auto prime=primeEnumerate(n);
    //for(int p:prime)for(int k=1;k*p<=n;k++)
    return v;
}