#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/extgcd.hpp"

/// @brief 一次不定方程式 ax+by=c を解く
/// @ref verify: https://atcoder.jp/contests/abc340/submissions/62495050
/**
*	g=gcd(a,b) とする。extGCD(a,b) によって、ax'+by'=g を解く。
*	両辺を c/g 倍し x=x'*(c/g),y=y'*(c/g) とすると、ax+by=c を満たす。c が g で割り切れない場合、解は存在しない。
*	ax+by=c の両辺を g で割ると、(a/g)*x + (b/g)*y = c/g となる。方程式の一般解を X,Y とおくと、(a/g)*(X-x) + (b/g)*(Y-y) = 0 を満たす。
*	a/g と b/g は互いに素なので X-x は b/g の倍数であり、X=(b/g)*t+x となる。
*	これを再代入すると、Y=-(a/g)*t+y を得る。
*/
struct BezoutIdentity {
    /// @brief ax+by=c
    BezoutIdentity(ll a, ll b, ll c) {
        this->a=a;
        this->b=b;
        this->c=c;
    }

    /// @brief 解が存在するか否かを返す
    bool build() {
        auto [g,X,Y]=ExtGcd(abs(a),abs(b));
        if(c%g!=0) return false;
        this->g=g,this->X=X,this->Y=Y;
        if(a<0) this->X=-this->X;
        if(b<0) this->Y=-this->Y;
        this->X*=c/g,this->Y*=c/g;
        return true;
    }

    /// @brief 一般解を返す
    pair<ll,ll> general_solution(ll t=0) {
        ll x=b/g*t+X,y=-a/g*t+Y;
        return {x,y};
    }

private:
    ll a,b,c,g;
    ll X,Y;
};