#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 二分探索
/// @details 条件 judge を満たす ok と ng の境界を二分探索によって求める。
/// @note O(log(|ok - ng|) * f)
template<typename T, typename Judge>
T BinarySearch(T ok, T ng, Judge judge) {
    while(abs(ok-ng)>1) {
        T mid=(ok+ng)/2;
        if(judge(mid)) ok=mid;
        else ng=mid;
    }
    return ok;
}

/// @brief 回数指定二分探索
/// @details 条件 judge を満たす ok と ng の境界を二分探索によって求める。
/// @note O(iter * f)
template<typename T, typename Judge>
T BinarySearchIteration(T ok, T ng, Judge judge, int iter=100) {
    while(iter--) {
        T mid=(ok+ng)/2;
        if(judge(mid)) ok=mid;
        else ng=mid;
    }
    return ok;
}

/// @brief 単調性の確認
/// @details 関数 judge が単調性を満たすか否かを確認する
/// @param start 開始要素
/// @param step 探索幅
/// @param iter 探索回数
template<typename T, typename Judge>
bool CheckMonotonicity(T start, T step, ll iter, Judge judge) {
    cerr<<"[ ";
    bool pre=false;
    ll cnt=0;
    for(T i=start; iter>0; iter--, i+=step) {
        bool tmp=judge(i);
        cerr<<"{ "<<i<<" : "<<(tmp ? "OK" : "NG")<<" }, ";
        if(i!=start&&tmp!=pre) cnt++;
        pre=tmp;
    }
    cerr<<" ]\n";

    if(cnt<=1) cerr<<"Is Monotonic\n";
    else cerr<<"Not Monotonicss\n";
    return cnt<=1;
}