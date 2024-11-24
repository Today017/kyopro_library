#include "../../kyopro_library/template.hpp"

namespace Bit{
	int popcount(int n){return __builtin_popcount(n);}
	int popcount(ll n){return __builtin_popcountll(n);}
	int parity(int n){return __builtin_parity(n);}
	int parity(ll n){return __builtin_parityll(n);}
	int topBit(int n){return n?31-__builtin_clz(n):-1;}
	int topBit(ll n){return n?63-__builtin_clzll(n):-1;}
	int lowBit(int n){return n?__builtin_ctz(n):-1;}
	int lowBit(ll n){return n?__builtin_ctzll(n):-1;}
	bool isPowerOfTwo(int n){return n&&(n&-n)==n;}
	ll mask(int n){return (1LL<<n)-1;}
	bool hasBit(ll n,int i){return (n>>i&1);}
}