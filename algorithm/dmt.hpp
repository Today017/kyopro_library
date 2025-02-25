#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/prime.hpp"

struct DivMulTransform{
	vector<int>primes;
	DivMulTransform(int n):primes(primeEnumerate(n)){}

	// 倍数高速ゼータ変換
	// v'[k] = Σ_{k|d} v[d] なる v' を返す。
	// O(|v| log(log(|v|)))
	template<typename Monoid>
	vector<typename Monoid::Type>multiple_zeta(vector<typename Monoid::Type>v){
		int n=v.size()-1;
		for(int p:primes)for(int k=n/p;k>0;k--)v[k]=Monoid::op(v[k],v[k*p]);
		return v;
	}

	// 約数高速ゼータ変換
	// v'[k] = Σ_{d|k} v[d] なる v' を返す。
	// O(|v| log(log(|v|)))
	template<typename Monoid>
	vector<typename Monoid::Type>divisor_zeta(vector<typename Monoid::Type>v){
		int n=v.size()-1;
		for(int p:primes)for(int k=1;k*p<=n;k++)v[k*p]=Monoid::op(v[k*p],v[k]);
		return v;
	}

	// 倍数高速メビウス変換
	// v'[k] = Σ_{k|d} μ(d) v[d] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// O(|v| log(log(|v|)))
	template<typename Abel>
	vector<typename Abel::Type>multiple_mobius(vector<typename Abel::Type>v){
		int n=v.size()-1;
		for(int p:primes)for(int k=1;k*p<=n;k++)v[k]=Abel::op(v[k],Abel::inv(v[k*p]));
		return v;
	}

	// 約数高速メビウス変換
	// v'[k] = Σ_{d|k} μ(d) v[k/d] なる v' を返す。
	// 逆変換が必要なので、v は可換群の元である必要がある。
	// O(|v| log(log(|v|)))
	template<typename Abel>
	vector<typename Abel::Type>divisor_mobius(vector<typename Abel::Type>v){
		int n=v.size()-1;
		for(int p:primes)for(int k=n/p;k>0;k--)v[k*p]=Abel::op(v[k*p],Abel::inv(v[k]));
		return v;
	}
};