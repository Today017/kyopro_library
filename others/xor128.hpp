#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 疑似乱数生成
ull Xor128(){
    static bool flag=false;
    static ull x=123456789,y=362436069,z=521288629,w=88675123;
    if(!flag){
        random_device seedgen;
        w=seedgen();
        flag=true;
    }
    ull t=x^(x<<11);
    x=y,y=z,z=w;
    return w=(w^(w>>19))^(t^(t>>8));
}
ll Xor128(ll n){ return Xor128()%n; }
ll Xor128(ll l, ll r){ return Xor128(r-l)+l; }//[l,r)
double Xor128Prob(){ return (double)Xor128()/(1ULL<<32); }