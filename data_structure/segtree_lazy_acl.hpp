#pragma once
#include<atcoder/lazysegtree>

template<typename Monoid, typename Operator, auto mapping>
auto LsgFactory(auto v) {
    auto op=[&](auto a, auto b) {
        return Operator::op(b,a);
    };
    auto mapping2=[&](auto f, auto x) {
        return mapping(x,f);
    };
    return atcoder::lazy_segtree<
        typename Monoid::Type,
        Monoid::op,
        Monoid::id,
        typename Operator::Type,
        mapping2,
        op,
        Operator::id
    >(v);
}