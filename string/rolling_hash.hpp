#include"../../kyopro_library/template.hpp"   
#include"../../kyopro_library/others/xor128.hpp"
#include"../../kyopro_library/others/modcal.hpp"

constexpr const int HASH_MAX=1000000;
constexpr const int HASH_C=256;
struct Hash {

    using Type=array<ll,5>;
    static VL base;
    static VVL inv,pow;
    static const VL mod;
    static bool flag;
    static array<array<ll,5>,256> num;

    Type value;

    void init() {
        if(flag) return;
        flag=true;
        base=VL(5); REP(i,5) base[i]=Xor128(3000,mod[i]);
        inv=VVL(5); pow=VVL(5);
        REP(i,5) {
            pow[i]=VL(HASH_MAX+1); inv[i]=VL(HASH_MAX+1);
            pow[i][0]=1; inv[i][HASH_MAX]=ModInv(ModPow<ll>(base[i],HASH_MAX,mod[i]),mod[i]);
            REP(j,HASH_MAX) {
                pow[i][j+1]=(pow[i][j]*base[i])%mod[i];
                inv[i][HASH_MAX-j-1]=(inv[i][HASH_MAX-j]*base[i])%mod[i];
            }
        }
        REP(i,HASH_C) REP(j,5) num[i][j]=Xor128(1,3000);
    }

    Hash()=default;
    Hash(const Hash& other) {
        if(!flag) init();
        value=other.value;
    }
    Hash(char c) {
        if(!flag) init();
        value.fill(0);
        REP(i,5) value[i]=num[c][i];
    }

    Hash& operator+=(const Hash& other) {
        REP(i,5) value[i]=(value[i]+other.value[i])%mod[i];
        return *this;
    }
    Hash& operator-=(const Hash& other) {
        REP(i,5) value[i]=(value[i]-other.value[i]+mod[i])%mod[i];
        return *this;
    }
    Hash operator+(const Hash& other) const {
        Hash ret=*this;
        ret+=other;
        return ret;
    }
    Hash operator-(const Hash& other) const {
        Hash ret=*this;
        ret-=other;
        return ret;
    }
    Hash shift(int x) const {
        Hash ret=*this;
        if(x<0) REP(i,5) (ret.value[i]*=inv[i][-x])%=mod[i];
        else REP(i,5) (ret.value[i]*=pow[i][x])%=mod[i];
        return ret;
    }
    bool operator==(const Hash& other) const {
        REP(i,5) if(value[i]!=other.value[i]) return false;
        return true;
    }
    Hash& operator=(const Hash& other) {
        REP(i,5) value[i]=other.value[i];
        return *this;
    }
};

VL Hash::base;
VVL Hash::inv;
VVL Hash::pow;
const VL Hash::mod={1000000007,1000000009,1000000021,1000000033,1000000087};
bool Hash::flag=false;
array<array<ll,5>,HASH_C> Hash::num={};


///@brief Rolling Hash
struct RollingHash{
    RollingHash()=default;
    vector<Hash> hash;

    /// @brief 文字列 s の Rolling Hash を構築する
    RollingHash(const string& s) {
        int n=s.size();
        hash=vector<Hash>(n+1);
        REP(i,n) hash[i+1]=hash[i]+Hash(s[i]).shift(i);
    }

    /// @brief 区間 [l, r) のハッシュ値を取得する
    Hash get(int l, int r) {
        Hash ret;
        ret=hash[r]-hash[l];
        ret=ret.shift(-l);
        return ret;
    }
};