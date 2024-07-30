#pragma once
#include "../../kyopro_library/template.hpp"

template <ll MOD>
struct ModInt {
    ll value;
    ModInt(ll x = 0) {
        if (x >= 0) {
            value = x % MOD;
        } else {
            value = MOD - (-x) % MOD;
        }
    }
    ModInt operator-() const {
        return ModInt(-value);
    }
    ModInt operator+() const {
        return ModInt(*this);
    }
    ModInt &operator+=(const ModInt &other) {
        value += other.value;
        if (value >= MOD) {
            value -= MOD;
        }
        return *this;
    }
    ModInt &operator-=(const ModInt &other) {
        value += MOD - other.value;
        if (value >= MOD) {
            value -= MOD;
        }
        return *this;
    }
    ModInt &operator*=(const ModInt other) {
        value = value * other.value % MOD;
        return *this;
    }
    ModInt &operator/=(ModInt other) {
        (*this) *= other.inv();
        return *this;
    }
    ModInt operator+(const ModInt &other) const {
        return ModInt(*this) += other;
    }
    ModInt operator-(const ModInt &other) const {
        return ModInt(*this) -= other;
    }
    ModInt operator*(const ModInt &other) const {
        return ModInt(*this) *= other;
    }
    ModInt operator/(const ModInt &other) const {
        return ModInt(*this) /= other;
    }
    ModInt pow(ll x) const {
        ModInt ret(1), mul(value);
        while (x) {
            if (x & 1) {
                ret *= mul;
            }
            mul *= mul;
            x >>= 1;
        }
        return ret;
    }
    ModInt inv() const {
        return pow(MOD - 2);
    }
    bool operator==(const ModInt &other) const {
        return value == other.value;
    }
    bool operator!=(const ModInt &other) const {
        return value != other.value;
    }
    friend ostream &operator<<(ostream &os, const ModInt &x) {
        return os << x.value;
    }
    friend istream &operator>>(istream &is, ModInt &x) {
        ll v;
        is >> v;
        x = ModInt<MOD>(v);
        return is;
    }
    static constexpr ll get_mod() {
        return MOD;
    }
};
using Mod998 = ModInt<998244353>;
using Mod107 = ModInt<1000000007>;
