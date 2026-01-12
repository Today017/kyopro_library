#include"../../kyopro_library/template.hpp"

///@brief 円環上での計算
namespace Ring {
    ///@brief 円環上で p1->p2 に+方向に移動する際に target を通過するかを判定する。
    ///@ref verify: https://atcoder.jp/contests/abc367/tasks/abc367_a
    bool BetweenIncrement(ll p1, ll p2, ll target) {
        if(p1==p2) return p1==target;
        return (target-p2)*(p2-p1)*(p1-target)>=0;
    }

    ///@brief 円環上で p1->p2 に-方向に移動する際に target を通過するかを判定する。
    bool BetweenDecrement(ll p1, ll p2, ll target) {
        swap(p1,p2);
        return BetweenIncrement(p1,p2,target);
    }

    ///@brief サイズ n の円環上で p1->p2 に移動する距離を返す。
    ll DistanceMin(ll p1, ll p2, ll n) {
        if(p1>p2) swap(p1,p2);
        return min(p2-p1,n-(p2-p1));
    }

    ///@brief サイズ n の円環上で p1->p2 に+方向に移動する距離を返す。
    ll DistanceIncrement(ll p1, ll p2, ll n) {
        return p1<p2 ? p2-p1 : (n+p2-p1)%n;
    }

    ///@brief サイズ n の円環上で p1->p2 に-方向に移動する距離を返す。
    ll DistanceDecrement(ll p1, ll p2, ll n) {
        return p1>p2 ? p1-p2 : (n+p1-p2)%n;
    }
}