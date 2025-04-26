#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 可換群
namespace Abel {
    /// @brief 和
    template<typename T>
    struct Sum {
        using Type=T;
        static Type id() { return T(0); }
        static Type op(const Type& a, const Type& b) { return a+b; }
        static Type inv(const Type& x) { return -x; }
    };

    /// @brief XOR
    template<typename T>
    struct Xor {
        using Type=T;
        static Type id() { return T(0); }
        static Type op(const Type& a, const Type& b) { return a^b; }
        static Type inv(const Type& x) { return x; }
    };
}