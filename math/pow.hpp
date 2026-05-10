#include"../../kyopro_library/template.hpp"

template<typename Monoid>
typename Monoid::Type MonoidPow(
    typename Monoid::Type X,
    ll N
) {
    using Type=typename Monoid::Type;
    Type ret=Monoid::id();
    while(N) {
        if(N&1) ret=Monoid::op(ret,X);
        X=Monoid::op(X,X);
        N>>=1;
    }
    return ret;
}
