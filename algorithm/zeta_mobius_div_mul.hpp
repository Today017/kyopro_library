#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/prime_enumerate.hpp"

/// @brief 倍数・約数ゼータ・メビウス変換
namespace ZetaMobiusDivMul {
    VI primes;
    void Init(int n=1e6) { primes=PrimeEnumerate(n); }

    /// @brief 倍数高速ゼータ変換
    /// @brief v'[k] = Σ_{k|d} v[d] なる v' を返す
    /// @note O(N log(log(N)))
    template<typename Monoid>
    vector<typename Monoid::Type> MultipleZeta(vector<typename Monoid::Type> v) {
        int n=v.size()-1;
        if((int)primes.size()<n) Init(n);
        for(int p:primes) for(int k=n/p; k>0; k--) v[k]=Monoid::op(v[k],v[k*p]);
        return v;
    }

    /// @brief 約数高速ゼータ変換
    /// @brief v'[k] = Σ_{d|k} v[d] なる v' を返す
    /// @note O(N log(log(N)))
    template<typename Monoid>
    vector<typename Monoid::Type> DivisorZeta(vector<typename Monoid::Type> v) {
        int n=v.size()-1;
        if((int)primes.size()<n) Init(n);
        for(int p:primes) for(int k=1; k*p<=n; k++) v[k*p]=Monoid::op(v[k*p],v[k]);
        return v;
    }

    /// @brief 倍数高速メビウス変換
    /// @brief v'[k] = Σ_{k|d} μ(d) v[d] なる v' を返す
    /// @note 逆変換が必要なので、v は可換群の元である必要がある
    /// @note O(N log(log(N)))
    template<typename Abel>
    vector<typename Abel::Type> MultipleMobius(vector<typename Abel::Type> v) {
        int n=v.size()-1;
        if((int)primes.size()<n) Init(n);
        for(int p:primes) for(int k=1; k*p<=n; k++) v[k]=Abel::op(v[k],Abel::inv(v[k*p]));
        return v;
    }

    /// @brief 約数高速メビウス変換
    /// @brief v'[k] = Σ_{d|k} μ(d) v[k/d] なる v' を返す
    /// @note 逆変換が必要なので、v は可換群の元である必要がある
    /// @note O(N log(log(N)))
    template<typename Abel>
    vector<typename Abel::Type> DivisorMobius(vector<typename Abel::Type> v) {
        int n=v.size()-1;
        if((int)primes.size()<n) Init(n);
        for(int p:primes) for(int k=n/p; k>0; k--) v[k*p]=Abel::op(v[k*p],Abel::inv(v[k]));
        return v;
    }
};

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/abel.hpp"