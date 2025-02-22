#include"../../kyopro_library/template.hpp"

template<typename T>
struct MultiSet:multiset<T>{
	using multiset<T>::multiset;
	T not_found;
	MultiSet()=default;
	MultiSet(T not_found=-1){this->not_found=not_found;}
	T min(){
		if(this->empty())return not_found;
		return*this->begin();
	}
	T max(){
		if(this->empty())return not_found;
		return*this->rbegin();
	}
	T pop_min(){
		if(this->empty())return not_found;
		T ret=min();
		this->erase(this->begin());
		return ret;
	}
	T pop_max(){
		if(this->empty())return not_found;
		T ret=max();
		this->erase(prev(this->end()));
		return ret;
	}  
	bool contains(T x){return this->find(x)!=this->end();}
	bool discard(T x){
		auto itr=this->find(x);
		if(itr==this->end())return false;
		this->erase(itr);
		return true;
	}
	T gt(T x){
		auto itr=this->upper_bound(x);
		if(itr==this->end())return not_found;
		return*itr;
	}
	T ge(T x){
		auto itr=this->lower_bound(x);
		if(itr==this->end())return not_found;
		return*itr;
	}
	T le(T x){
		auto itr=this->upper_bound(x);
		if(itr==this->begin())return not_found;
		return*prev(itr);
	}
	T lt(T x){
		auto itr=this->lower_bound(x);
		if(itr==this->begin())return not_found;
		return*prev(itr);
	}
};