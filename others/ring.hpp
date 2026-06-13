#pragma once
#include"../../kyopro_library/template.hpp"

///@brief 環・半環
namespace Ring {
    template<typename T>
    struct PlusMul {
        using Type=T;
        static Type plus(const Type& l, const Type& r) { return l+r; }
        static Type inv(const Type& x) { return -x; }
        static Type mul(const Type& l, const Type& r) { return l*r; }
        static Type zero() { return 0; }
        static Type one() { return 1; }
    };

    template<typename T, T max_value>
    struct MinPlus {
        using Type=T;
        static Type plus(const Type& l, const Type& r) { return min(l,r); }
        static Type mul(const Type& l, const Type& r) { return l+r; }
        static Type zero() { return max_value; }
        static Type one() { return 0; }
    };

    template<typename T, T min_value>
    struct MaxPlus {
        using Type=T;
        static Type plus(const Type& l, const Type& r) { return max(l,r); }
        static Type mul(const Type& l, const Type& r) { return l+r; }
        static Type zero() { return min_value; }
        static Type one() { return 0; }
    };
}
