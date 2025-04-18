#pragma once
#include"../../kyopro_library/template.hpp"

/// @file modint.hpp
/// @brief ModInt
template<ll MOD>
struct ModInt{
    ModInt(ll x=0){ value=(x>=0?x%MOD:MOD-(-x)%MOD); }

    ModInt operator-() const { return ModInt(-value); }
    ModInt operator+() const { return ModInt(*this); }
    Modint& operator+=(const Modint& other){
        value+=other.value;
        if(value>=MOD) value-=MOD;
        return*this;
    }
    Modint& operator-=(const Modint& other){
        value+=MOD-other.value;
        if(value>=MOD) value-=MOD;
        return*this;
    }
    Modint& operator*=(const ModInt other){
        value=value*other.value%MOD;
        return*this;
    }
    Modint& operator/=(ModInt other){
        (*this)*=other.inv();
        return*this;
    }
    ModInt operator+(const Modint& other) const { return ModInt(*this)+=other; }
    ModInt operator-(const Modint& other) const { return ModInt(*this)-=other; }
    ModInt operator*(const Modint& other) const { return ModInt(*this)*=other; }
    ModInt operator/(const Modint& other) const { return ModInt(*this)/=other; }
    bool operator==(const Modint& other) const { return value==other.value; }
    bool operator!=(const Modint& other) const { return value!=other.value; }
    friend ostream& operator<<(ostream& os, const Modint& x){ return os<<x.value; }
    friend istream& operator>>(istream& is, Modint& x){
        ll v;
        is>>v;
        x=ModInt<MOD>(v);
        return is;
    }

    ModInt pow(ll x) const { 
        ModInt ret(1),mul(value);
        while(x){
            if(x&1) ret*=mul;
            mul*=mul;
            x>>=1;
        }
        return ret;
    }
    ModInt inv() const { return pow(MOD-2); }
    ll val(){return value; }
    static constexpr ll get_mod(){ return MOD; }

private:
    ll value;
};

using Mod998=ModInt<998244353>;
using Mod107=ModInt<1000000007>;
using VM=vector<Mod998>;