#include"../../kyopro_library/template.hpp"

template<typename T,typename Judge>
T binarySearch(T ok,T ng,Judge judge){
	while(abs(ok-ng)>1){
		T mid=(ok+ng)/2;
		(judge(mid)?ok:ng)=mid;
	}
	return ok;
}

template<typename T,typename Judge>
T binarySearchIteration(T ok,T ng,Judge judge,int iter=100){
	while(iter--){
		T mid=(ok+ng)/2;
		(judge(mid)?ok:ng)=mid;
	}
	return ok;
}