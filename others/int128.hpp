#pragma once
#include"../../kyopro_library/template.hpp"

constexpr lll operator ""_lll(ull x) { return static_cast<lll>(x); }
constexpr const lll INFLL=1_lll<<120;

istream& operator>>(istream& is, lll& x) {
	int c=is.peek();
	while(c==' '||c=='\n') is.get(), c=is.peek();
	bool neg=false;
	if(c=='-') neg=true, is.get();
	x=0;
	while(isdigit(is.peek())) x=x*10+is.get()-'0';
	if(neg) x=-x;
	return is;
}

ostream& operator<<(ostream& os, lll x) {
	if(x<0) os<<'-', x=-x;
	if(x==0) return os<<'0';
	string s;
	while(x>0) s+=x%10+'0', x/=10;
    reverse(s.begin(),s.end());
	return os<<s;
}

#ifdef TDY
lll abs(lll x) { if (x<0) return -x; return x; }
lll gcd(lll a, lll b) {
    while(b) a%=b, swap(a,b);
    return a;
}
#endif
