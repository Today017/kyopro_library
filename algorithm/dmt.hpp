#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/prime.hpp"

namespace DivMulTransform{
	vector<int>primes;
	void init(int n=1e6){ primes=primeEnumerate(n); }

	// 倍数高速ゼータ変換
	// v'[k] = Σ_{k|d} v[d] なる v' を返す。
	// O(|v| log(log(|v|)))
	template<typename Monoid>
	vector<typename Monoid::Type>multipleZeta(vector<typename Monoid::Type>v){
		int n=v.size()-1;
		if((int)primes.size()<n)init(n);
		for(int p:primes)for(int k=n/p;k>0;k--)v[k]=Monoid::op(v[k],v[k*p]);
		return v;
	}

	// 約数高速ゼータ変換
	// v'[k] = Σ_{d|k} v[d] なる v' を返す。
	// O(|v| log(log(|v|)))
	template<typename Monoid>
	vector<typename Monoid::Type>divisorZeta(vector<typename Monoid::Type>v){
		int n=v.size()-1;
		if((int)primes.size()<n)init(n);
		for(int p:primes)for(int k=1;k*p<=n;k++)v[k*p]=Monoid::op(v[k*p],v[k]);
		return v;
	}

	// 倍数高速メビウス変換
	// v'[k] = Σ_{k|d} μ(d) v[d] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// O(|v| log(log(|v|)))
	template<typename Abel>
	vector<typename Abel::Type>multipleMobius(vector<typename Abel::Type>v){
		int n=v.size()-1;
		if((int)primes.size()<n)init(n);
		for(int p:primes)for(int k=1;k*p<=n;k++)v[k]=Abel::op(v[k],Abel::inv(v[k*p]));
		return v;
	}

	// 約数高速メビウス変換
	// v'[k] = Σ_{d|k} μ(d) v[k/d] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// O(|v| log(log(|v|)))
	template<typename Abel>
	vector<typename Abel::Type>divisorMobius(vector<typename Abel::Type>v){
		int n=v.size()-1;
		if((int)primes.size()<n)init(n);
		for(int p:primes)for(int k=n/p;k>0;k--)v[k*p]=Abel::op(v[k*p],Abel::inv(v[k]));
		return v;
	}
};