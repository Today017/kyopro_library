#pragma once
#include"../../kyopro_library/template.hpp"

/// @file monoid.hpp
/// @brief モノイド
namespace Monoid{
	/// @brief Min モノイド
	/// @tparam max_value 単位元
	template<typename T,T max_value=INF>
	struct Min{
		using Type=T;
		static Type id(){return max_value;}
		static Type op(const Type&a,const Type&b){return min(a,b);}
	};

	/// @brief Max モノイド
	/// @tparam min_value 単位元
	template<typename T,T min_value=-INF>
	struct Max{
		using Type=T;
		static Type id(){return min_value;}
		static Type op(const Type&a,const Type&b){return max(a,b);}
	};

	/// @brief 和
	template<typename T>
	struct Sum{
		using Type=T;
		static Type id(){return 0;}
		static Type op(const Type&a,const Type&b){return a+b;}
	};

	/// @brief （和，区間の長さ）
	template<typename T>
	struct SumPair{
		using Type=pair<T,int>;
		static Type id(){return make_pair(T(0),0);}
		static Type op(const Type&a,const Type&b){return{a.first+b.first,a.second+b.second};}
	};
}