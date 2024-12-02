#pragma once
#include"../../kyopro_library/template.hpp"

template<typename T,T not_exist>
struct UpdateOperator{
	using Type=T;
	static Type id(){return not_exist;}
	static Type op(const Type&a,const Type&b){return b==id()?a:b;}
};

template<typename T>
struct AddOperator{
	using Type=T;
	static Type id(){return 0;}
	static Type op(const Type&a,const Type&b){return a+b;}
};

template<typename T>
struct UpdateOperatorTimeStamp{
	using Type=pair<T,int>;
	static Type id(){return {0,-1};}
	static Type op(const Type&a,const Type&b){return b.second>a.second?b:a;}
};
