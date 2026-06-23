#pragma once
#include "../../kyopro_library/base/include.hpp"

using i16=short;
using i32=int;
using i64=long long;
using i128=__int128_t;
using u16=unsigned short;
using u32=unsigned int;
using u64=unsigned long long;
using u128=__uint128_t;
using f64=double;
using f80=long double;

using ii=i64; using ll=i64; using ull=u64;
using vi=vector<ii>; using vvi=vector<vector<ii>>; using vvvi=vector<vector<vector<ii>>>;
using vl=vector<ll>; using vvl=vector<vector<ll>>; using vvvl=vector<vector<vector<ll>>>;
using ii3=array<ii,3>; using ii4=array<ii,4>; using ii5=array<ii,5>;
using lll=i128; using ulll=u128; constexpr lll operator ""_lll(ull x) { return static_cast<lll>(x); }
using ld=f80;
using str=string;
using vstr=vector<str>;

template<typename T> using V=vector<T>;
template<typename T> using VV=vector<vector<T>>;
template<typename T> using VVV=vector<vector<vector<T>>>;
template<typename T> using VVVV=vector<vector<vector<vector<T>>>>;
template<typename T> using VVVVV=vector<vector<vector<vector<vector<T>>>>>;
template<typename T> using VVVVVV=vector<vector<vector<vector<vector<vector<T>>>>>>;

template<typename T> using max_pq=priority_queue<T>;
template<typename T> using min_pq=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using unset=unordered_set<T>;
template<typename T, typename T2> using unmap=unordered_map<T,T2>;

template <typename T, typename U>
struct PR: pair<T, U> {
    template<typename... Args> PR(Args... args): pair<T,U>(args...) {}
    using pair<T,U>::first;
    using pair<T,U>::second;
    PR& operator+=(const PR& r) { first+=r.first; second+=r.second; return *this; }
    PR& operator-=(const PR& r) { first-=r.first; second-=r.second; return *this; }
    PR& operator*=(const PR& r) { first*=r.first; second*=r.second; return *this; }
    template<typename S> PR& operator+=(const S& r) { first+=r; second+=r; return *this; }
    template<typename S> PR& operator-=(const S& r) { first-=r; second-=r; return *this; }
    template<typename S> PR& operator*=(const S& r) { first*=r; second*=r; return *this; }
    PR operator+(const PR& r) const { return PR(*this)+=r; }
    PR operator-(const PR& r) const { return PR(*this)-=r; }
    PR operator*(const PR& r) const { return PR(*this)*=r; }
    template <typename S> PR operator+(const S& r) const { return PR(*this)+=r; }
    template <typename S> PR operator-(const S& r) const { return PR(*this)-=r; }
    template <typename S> PR operator*(const S& r) const { return PR(*this)*=r; }
    PR operator-() const { return PR{-first,-second}; }
};
using pi=PR<ii,ii>; using vpi=vector<pi>; using vvpi=vector<vector<pi>>;
using pl=PR<ll,ll>; using vpl=vector<pl>; using vvpl=vector<vector<pl>>;

template <typename T, typename U, typename V>
struct TR: tuple<T, U, V> {
    using tuple<T, U, V>::tuple;
    T& x = get<0>(*this);
    U& y = get<1>(*this);
    V& z = get<2>(*this);
    TR() : tuple<T, U, V>() {}
    TR(const T& a, const U& b, const V& c) : tuple<T, U, V>(a, b, c) {}
    TR(const TR& other) : tuple<T, U, V>(other), x(get<0>(*this)), y(get<1>(*this)), z(get<2>(*this)) {}
    TR(TR&& other) noexcept : tuple<T, U, V>(move(other)), x(get<0>(*this)), y(get<1>(*this)), z(get<2>(*this)) {}
    TR& operator=(const TR& other) { tuple<T, U, V>::operator=(other); return *this; }
    TR& operator=(TR&& other) noexcept { tuple<T, U, V>::operator=(move(other)); return *this; }
};
using ti=TR<ii,ii,ii>; using vti=vector<ti>; using vvti=vector<vector<ti>>;
using tl=TR<ll,ll,ll>; using vtl=vector<ti>; using vvtl=vector<vector<tl>>;

const i32  INF=1e9+10;
const i64  INFL=4e18;
const i128 INFLL=1_lll<<120;

template<typename T> constexpr T inf=0;
template<> constexpr i32  inf<i32 > =INF;
template<> constexpr i64  inf<i64 > =INFL;
template<> constexpr i128 inf<i128> =INFLL;
template<> constexpr u32  inf<u32 > =INF;
template<> constexpr u64  inf<u64 > =INFL;
template<> constexpr u128 inf<u128> =INFLL;
template<> constexpr f64  inf<f64 > =numeric_limits<f64>::infinity();
template<> constexpr f80  inf<f80 > =numeric_limits<f80>::infinity();

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
    reverse(all(s));
	return os<<s;
}

#ifdef TDY
lll abs(lll x) { if (x<0) return -x; return x; }
lll gcd(lll a, lll b) {
    while(b) a%=b, swap(a,b);
    return a;
}
#endif
