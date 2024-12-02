#pragma once
#include"../../kyopro_library/template.hpp"

template<typename T>
struct AdditiveAbel{
	using Type=T;
	static Type id(){return T(0);}
	static Type op(const Type&a,const Type&b){return a+b;}
	static Type inv(const Type&x){return -x;}
};
