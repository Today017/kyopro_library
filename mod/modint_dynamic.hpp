#include"../../kyopro_library/template.hpp"

/// @brief 実行時に mod を変更できる ModInt
struct ModIntDynamic {
    ll value;
    static ll mod;
    static void set_mod(ll x) { mod=x; }
    static ll get_mod() { return mod; }
    ModIntDynamic(ll x=0) {
        if(x>=0) value=x%mod;
        else value=mod-(-x)%mod;
    }
    ModIntDynamic operator-() const { return ModIntDynamic(-value); }
    ModIntDynamic operator+() const { return ModIntDynamic(*this); }
    ModIntDynamic& operator+=(const ModIntDynamic& other) {
        value+=other.value;
        if(value>=mod) value-=mod;
        return*this;
    }
    ModIntDynamic& operator-=(const ModIntDynamic& other) {
        value+=mod-other.value;
        if(value>=mod) value-=mod;
        return*this;
    }
    ModIntDynamic& operator*=(const ModIntDynamic other) {
        value=value*other.value%mod;
        return*this;
    }
    ModIntDynamic& operator/=(ModIntDynamic other) {
        (*this)*=other.inv();
        return*this;
    }
    ModIntDynamic operator+(const ModIntDynamic& other) const { return ModIntDynamic(*this)+=other; }
    ModIntDynamic operator-(const ModIntDynamic& other) const { return ModIntDynamic(*this)-=other; }
    ModIntDynamic operator*(const ModIntDynamic& other) const { return ModIntDynamic(*this)*=other; }
    ModIntDynamic operator/(const ModIntDynamic& other) const { return ModIntDynamic(*this)/=other; }
    ModIntDynamic pow(ll x) const {
        ModIntDynamic ret(1),mul(value);
        while(x) {
            if(x&1) ret*=mul;
            mul*=mul;
            x>>=1;
        }
        return ret;
    }
    ModIntDynamic inv() const { return pow(mod-2); }
    bool operator==(const ModIntDynamic& other) const { return value==other.value; }
    bool operator!=(const ModIntDynamic& other) const { return value!=other.value; }
    friend ostream& operator<<(ostream& os, const ModIntDynamic& x) { return os<<x.value; }
    friend istream& operator>>(istream& is, ModIntDynamic& x) {
        ll v;
        is>>v;
        x=ModIntDynamic(v);
        return is;
    }
};
ll ModIntDynamic::mod=998244353;