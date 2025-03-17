#pragma once
#include"../../kyopro_library/template.hpp"

namespace Abel{
	template<typename T>
	struct Additive{
		using Type=T;
		static Type id(){return T(0);}
		static Type op(const Type&a,const Type&b){return a+b;}
		static Type inv(const Type&x){return -x;}
	};

	template<typename T>
	struct Xor{
		using Type=T;
		static Type id(){return T(0);}
		static Type op(const Type&a,const Type&b){return a^b;}
		static Type inv(const Type&x){return x;}
	};
}