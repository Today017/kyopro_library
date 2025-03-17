#pragma once
#include"../../kyopro_library/template.hpp"

namespace Monoid{
	template<typename T,T max_value=INF>
	struct Min{
		using Type=T;
		static Type id(){return max_value;}
		static Type op(const Type&a,const Type&b){return min(a,b);}
	};

	template<typename T,T min_value=-INF>
	struct Max{
		using Type=T;
		static Type id(){return min_value;}
		static Type op(const Type&a,const Type&b){return max(a,b);}
	};

	template<typename T>
	struct Sum{
		using Type=T;
		static Type id(){return 0;}
		static Type op(const Type&a,const Type&b){return a+b;}
	};

	template<typename T>
	struct SumPair{
		using Type=pair<T,int>;
		static Type id(){return make_pair(T(0),0);}
		static Type op(const Type&a,const Type&b){return{a.first+b.first,a.second+b.second};}
	};
}