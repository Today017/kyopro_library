#include "../../kyopro_library/template.hpp"

///@brief ビット演算
namespace Bit {
    ///@brief 1であるビットの個数を返す
    int PopCount(int n) { return __builtin_popcount(n); }

    ///@brief 1であるビットの個数を返す
    int PopCount(ll n) { return __builtin_popcountll(n); }

    ///@brief popcountの偶奇を返す
    int Parity(int n) { return __builtin_parity(n); }

    ///@brief popcountの偶奇を返す
    int Parity(ll n) { return __builtin_parityll(n); }

    ///@brief 最上位ビットの位置を返す
    int TopBit(int n) { return n ? 31-__builtin_clz(n) : -1; }

    ///@brief 最上位ビットの位置を返す
    int TopBit(ll n) { return n ? 63-__builtin_clzll(n) : -1; }

    ///@brief 2進表現の長さを返す
    int BitLength(int n) { return n ? 32-__builtin_clz(n) : 1; }

    ////@brief 2進表現の長さを返す
    int BitLength(ll n) { return n ? 64-__builtin_clzll(n) : 1; }

    ///@brief 最下位ビットの位置を返す
    int LowBit(int n) { return n ? __builtin_ctz(n) : -1; }

    ///@brief 最下位ビットの位置を返す
    int LowBit(ll n) { return n ? __builtin_ctzll(n) : -1; }

    ///@brief 2のべき乗か否かを返す
    bool IsPowerOfTwo(int n) { return n && (n&-n)==n; }

    ///@brief 0~n-1ビットを立てたビットマスクを返す
    ll Mask(int n) { return (1LL<<n)-1; }

    ///@brief iビット目が立っているか否かを返す
    bool HasBit(ll n,int i) { return (n>>i&1); }

    ///@brief sの部分集合を返す
    vector<int> Subset(int s) {
        vector<int> ret;
        int t=s;
        do { ret.push_back(t); --t&=s; } while(t!=s);
        return ret;
    }

    ///@brief 整数nの2進表現を返す
    ///@param len ビット数
    ///@param rev 反転するか否か
    string ToBinary(ll n, int len=32, bool rev=false) {
        string ret;
        rep(i,len) ret+=(HasBit(n,rev? len-1-i: i)? '1': '0');
        return ret;
    }
}
