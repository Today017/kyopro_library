#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/math/prime_enumerate.hpp"

/// @brief 倍数・約数ゼータ・メビウス変換
namespace ZetaMobiusDivMul {
    vi primes;
    void Init(int N = 1e6) { primes = PrimeEnumerate(N); }

    /// @brief 倍数高速ゼータ変換
    /// @brief V'[k] = Σ_{k|d} V[d] なる V' を返す
    /// @note O(N log(log(N)))
    template <typename Monoid>
    vector<typename Monoid::Type> MultipleZeta(vector<typename Monoid::Type> V) {
        int N = V.size() - 1;
        if(primes.size() < N) Init(N);
        for(int p : primes) {
            if(p > N) break;
            for(int k = N / p; k > 0; k--) V[k] = Monoid::op(V[k], V[k * p]);
        }
        return V;
    }

    /// @brief 約数高速ゼータ変換
    /// @brief V'[k] = Σ_{d|k} V[d] なる V' を返す
    /// @note O(N log(log(N)))
    template <typename Monoid>
    vector<typename Monoid::Type> DivisorZeta(vector<typename Monoid::Type> V) {
        int N = V.size() - 1;
        if(primes.size() < N) Init(N);
        for(int p : primes) {
            if(p > N) break;
            for(int k = 1; k * p <= N; k++) V[k * p] = Monoid::op(V[k * p], V[k]);
        }
        return V;
    }

    /// @brief 倍数高速メビウス変換
    /// @brief V'[k] = Σ_{k|d} μ(d) V[d] なる V' を返す
    /// @note 逆変換が必要なので、v は可換群の元である必要がある
    /// @note O(N log(log(N)))
    template <typename Abel>
    vector<typename Abel::Type> MultipleMobius(vector<typename Abel::Type> V) {
        int N = V.size() - 1;
        if(primes.size() < N) Init(N);
        for(int p : primes) {
            if(p > N) break;
            for(int k = 1; k * p <= N; k++) V[k] = Abel::op(V[k], Abel::inv(V[k * p]));
        }
        return V;
    }

    /// @brief 約数高速メビウス変換
    /// @brief V'[k] = Σ_{d|k} μ(d) V[k/d] なる V' を返す
    /// @note 逆変換が必要なので、v は可換群の元である必要がある
    /// @note O(N log(log(N)))
    template <typename Abel>
    vector<typename Abel::Type> DivisorMobius(vector<typename Abel::Type> V) {
        int N = V.size() - 1;
        if(primes.size() < N) Init(N);
        for(int p : primes) {
            if(p > N) break;
            for(int k = N / p; k > 0; k--) V[k * p] = Abel::op(V[k * p], Abel::inv(V[k]));
        }
        return V;
    }
};  // namespace ZetaMobiusDivMul

/// @brief LCM/GCD Convolution
namespace ConvolutionDivMul {
    /// @brief Gcd Convolution
    /// @brief C[i] = Σ_{gcd(j,k)=i} A[j]*B[k]
    /// @note O(N log(log(N)))
    /// @tparam Ring 計算を行う環
    template <typename Ring>
    vector<typename Ring::Type> GcdConvolution(
        vector<typename Ring::Type> A,
        vector<typename Ring::Type> B) {
        using Type = typename Ring::Type;
        int N = max(A.size(), B.size());
        if(ZetaMobiusDivMul::primes.size() < N) ZetaMobiusDivMul::Init(N);

        struct Abel {
            using Type = typename Ring::Type;
            static Type op(const Type& l, const Type& r) { return Ring::plus(l, r); }
            static Type inv(const Type& x) { return Ring::inv(x); }
            static Type id() { return Ring::zero(); }
        };

        A = move(ZetaMobiusDivMul::MultipleZeta<Abel>(A));
        B = move(ZetaMobiusDivMul::MultipleZeta<Abel>(B));
        rep(i, N) A[i] = Ring::mul(A[i], B[i]);
        A = move(ZetaMobiusDivMul::MultipleMobius<Abel>(A));

        return A;
    }

    /// @brief Lcm Convolution
    /// @brief C[i] = Σ_{lcm(j,k)=i} A[j]*B[k]
    /// @note O(N log(log(N)))
    /// @tparam Ring 計算を行う環
    template <typename Ring>
    vector<typename Ring::Type> LcmConvolution(
        vector<typename Ring::Type> A,
        vector<typename Ring::Type> B) {
        using Type = typename Ring::Type;
        int N = max(A.size(), B.size());
        if(ZetaMobiusDivMul::primes.size() < N) ZetaMobiusDivMul::Init(N);

        struct Abel {
            using Type = typename Ring::Type;
            static Type op(const Type& l, const Type& r) { return Ring::plus(l, r); }
            static Type inv(const Type& x) { return Ring::inv(x); }
            static Type id() { return Ring::zero(); }
        };

        A = move(ZetaMobiusDivMul::DivisorZeta<Abel>(A));
        B = move(ZetaMobiusDivMul::DivisorZeta<Abel>(B));
        rep(i, N) A[i] = Ring::mul(A[i], B[i]);
        A = move(ZetaMobiusDivMul::DivisorMobius<Abel>(A));

        return A;
    }
}  // namespace ConvolutionDivMul

#include "../../kyopro_library/others/monoid.hpp"
#include "../../kyopro_library/others/abel.hpp"
#include "../../kyopro_library/others/ring.hpp"
