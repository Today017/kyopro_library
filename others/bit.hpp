#include "../../kyopro_library/template.hpp"

/// @brief ビット演算
namespace Bit{
	int PopCount(int n){return __builtin_popcount(n);}
	int PopCount(ll n){return __builtin_popcountll(n);}
	int Parity(int n){return __builtin_parity(n);}
	int Parity(ll n){return __builtin_parityll(n);}
	int TopBit(int n){return n?31-__builtin_clz(n):-1;}
	int TopBit(ll n){return n?63-__builtin_clzll(n):-1;}
	int LowBit(int n){return n?__builtin_ctz(n):-1;}
	int LowBit(ll n){return n?__builtin_ctzll(n):-1;}
	bool IsPowerOfTwo(int n){return n&&(n&-n)==n;}
	ll Mask(int n){return (1LL<<n)-1;}
	bool HasBit(ll n,int i){return (n>>i&1);}
	string ToBinary(ll n,int len=32,bool rev=false){
		string ret;
		for(int i=0;i<len;i++)ret+=HasBit(n,rev?len-1-i:i)?'1':'0';
		return ret;
	}
}