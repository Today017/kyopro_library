#include"../../kyopro_library/template.hpp"

template<typename T=ll>
struct Fraction{
	T upper,lower;
	Fraction()=default;
	Fraction(T a,T b){
		T g=gcd(a,b);
		upper=a/g,lower=b/g;
		if(lower<0)upper*=-1,lower*=-1;
	}
	Fraction(T a=0){upper=a,lower=1;}
	Fraction operator+(const Fraction&f){return Fraction(upper*f.lower+f.upper*lower,lower*f.lower);}
	Fraction operator-(const Fraction&f){return Fraction(upper*f.lower-f.upper*lower,lower*f.lower);}
	Fraction operator*(const Fraction&f){return Fraction(upper*f.upper,lower*f.lower);}
	Fraction operator/(const Fraction&f){return Fraction(upper*f.lower,lower*f.upper);}
	Fraction operator+=(const Fraction&f){return*this=*this+f;}
	Fraction operator-=(const Fraction&f){return*this=*this-f;}
	Fraction operator*=(const Fraction&f){return*this=*this*f;}
	Fraction operator/=(const Fraction&f){return*this=*this/f;}
	Fraction operator+(const T&f){return Fraction(upper+f*lower,lower);}
	Fraction operator-(const T&f){return Fraction(upper-f*lower,lower);}
	Fraction operator*(const T&f){return Fraction(upper*f,lower);}
	Fraction operator/(const T&f){return Fraction(upper,lower*f);}
	Fraction operator+=(const T&f){return*this=*this+f;}
	Fraction operator-=(const T&f){return*this=*this-f;}
	Fraction operator*=(const T&f){return*this=*this*f;}
	Fraction operator/=(const T&f){return*this=*this/f;}
	Fraction operator-(){return Fraction(-upper,lower);}
	bool operator==(const Fraction&f)const{return upper==f.upper&&lower==f.lower;}
	bool operator!=(const Fraction&f)const{return upper!=f.upper||lower!=f.lower;}
	bool operator<(const Fraction&f)const{return upper*f.lower<f.upper*lower;}
	bool operator<=(const Fraction&f)const{return upper*f.lower<=f.upper*lower;}
	bool operator>(const Fraction&f)const{return upper*f.lower>f.upper*lower;}
	bool operator>=(const Fraction&f)const{return upper*f.lower>=f.upper*lower;}
	bool operator==(const T&f)const{return upper==f&&lower==1;}
	bool operator!=(const T&f)const{return upper!=f||lower!=1;}
	bool operator<(const T&f)const{return upper<f*lower;}
	bool operator<=(const T&f)const{return upper<=f*lower;}
	bool operator>(const T&f)const{return upper>f*lower;}
	bool operator>=(const T&f)const{return upper>=f*lower;}
	friend ostream&operator<<(ostream&os,const Fraction&f){
		os<<f.upper<<"/"<<f.lower;
		return os;
	}

private:
    T gcd(T a,T b){
        while(b!=0){
            T r=a%b;
            a=b;
            b=r;
        }
        return a;
    }
};