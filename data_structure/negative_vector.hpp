#include"../../kyopro_library/template.hpp"

template<typename T>
struct OffsetVector:vector<T>{
	int offset=0;
	OffsetVector()=default;
	OffsetVector(int lo,int hi,T init){
		assert(lo<=hi);
		this->assign(hi-lo+1,init);
		offset=-lo;
	}
	T&operator[](int i){
		assert(i+offset>=0);
		return vector<T>::operator[](i+offset);
	}
	T operator[](int i)const{
		assert(i+offset>=0);
		return vector<T>::operator[](i+offset);
	}
};
