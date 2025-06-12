#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 素数列挙
/// @details n 以下の素数の配列を返す
/// @note O(n log(log(n)))
vector<int> PrimeEnumerate(int n) {
    vector<int> prime,is_prime(n+1,true);
    is_prime[0]=is_prime[1]=false;
    for(int i=2; i<=n; i++) {
        if(is_prime[i]) {
            prime.push_back(i);
            for(int j=2*i; j<=n; j+=i) is_prime[j]=false;
        }
    }
    return prime;
}