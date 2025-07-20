#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief 作用素
namespace Operator {
    /// @brief 更新
    template<typename T, T not_exist>
    struct Update {
        using Type=T;
        static Type id() { return not_exist; }
        static Type op(const Type& a, const Type& b) { return b==id() ? a : b; }
    };

    /// @brief 加算
    template<typename T>
    struct Add {
        using Type=T;
        static Type id() { return 0; }
        static Type op(const Type& a, const Type& b) { return a+b; }
    };

    /// @brief 可換な更新（タイムスタンプ）
    template<typename T>
    struct UpdateTimeStamp {
        using Type=pair<T,int>;
        static Type id() { return {0,-1}; }
        static Type op(const Type& a, const Type& b) { return b.second>a.second ? b : a; }
    };
}