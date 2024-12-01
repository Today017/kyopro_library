#pragma once
#include"../../kyopro_library/template.hpp"

template<typename T,T max_value=INF>
struct MinMonoid{
	using Type=T;
	static Type id(){return max_value;}
	static Type op(Type a,Type b){return min(a,b);}
};

template<typename T,T min_value=-INF>
struct MaxMonoid{
	using Type=T;
	static Type id(){return min_value;}
	static Type op(Type a,Type b){return max(a,b);}
};

template<typename T>
struct SumMonoid{
	using Type=T;
	static Type id(){return 0;}
	static Type op(Type a,Type b){return a+b;}
};

template<typename T>
struct PairSumMonoid{
	using Type=pair<T,int>;
	static Type id(){return make_pair(T(0),0);}
	static Type op(Type a,Type b){return{a.first+b.first,a.second+b.second};}
};