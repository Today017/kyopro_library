#pragma once
#include"../../kyopro_library/template.hpp"

// 素数列挙
// n 以下の素数の配列を返す。
// O(n log(log(n)))
vector<int>primeEnumerate(int n){
    vector<int>prime;
    vector<bool>is_prime(n+1,true);
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++){
        if(is_prime[i]){
            prime.push_back(i);
            for(int j=2*i;j<=n;j+=i)is_prime[j]=false;
        }
    }
    return prime;
}