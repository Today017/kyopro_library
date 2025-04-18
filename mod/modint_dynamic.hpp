#include"../../kyopro_library/template.hpp"

struct DynamicModInt{
	ll value;
	static ll mod;
	static void set_mod(ll x){mod=x;}
	static ll get_mod(){return mod;}
	DynamicModInt(ll x=0){
		if(x>=0){
			value=x%mod;
		}else{
			value=mod-(-x)%mod;
		}
	}
	DynamicModInt operator-()const{return DynamicModInt(-value);}
	DynamicModInt operator+()const{return DynamicModInt(*this);}
	DynamicModInt&operator+=(const DynamicModInt&other){
		value+=other.value;
		if(value>=mod)value-=mod;
		return*this;
	}
	DynamicModInt&operator-=(const DynamicModInt&other){
		value+=mod-other.value;
		if(value>=mod)value-=mod;
		return*this;
	}
	DynamicModInt&operator*=(const DynamicModInt other){
		value=value*other.value%mod;
		return*this;
	}
	DynamicModInt&operator/=(DynamicModInt other){
		(*this)*=other.inv();
		return*this;
	}
	DynamicModInt operator+(const DynamicModInt&other)const{return DynamicModInt(*this)+=other;}
	DynamicModInt operator-(const DynamicModInt&other)const{return DynamicModInt(*this)-=other;}
	DynamicModInt operator*(const DynamicModInt&other)const{return DynamicModInt(*this)*=other;}
	DynamicModInt operator/(const DynamicModInt&other)const{return DynamicModInt(*this)/=other;}
	DynamicModInt pow(ll x)const{
		DynamicModInt ret(1),mul(value);
		while(x){
			if(x&1)ret*=mul;
			mul*=mul;
			x>>=1;
		}
		return ret;
	}
	DynamicModInt inv()const{return pow(mod-2);}
	bool operator==(const DynamicModInt&other)const{return value==other.value;}
	bool operator!=(const DynamicModInt&other)const{return value!=other.value;}
	friend ostream&operator<<(ostream&os,const DynamicModInt&x){return os<<x.value;}
	friend istream&operator>>(istream&is,DynamicModInt&x){
		ll v;
		is>>v;
		x=DynamicModInt(v);
		return is;
	}
};
ll DynamicModInt::mod=998244353;