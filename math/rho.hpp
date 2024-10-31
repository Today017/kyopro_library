#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/ptest.hpp"

//ポラードのロー法による素因数分解
//O(N^(1/4))
//verify:https://algo-method.com/tasks/553
vector<pair<ll,ll>>primeFactorize(ll n){
	if(primalityTest(n))return{{n,1}};
	auto find_factor=[](auto&&find_factor,ll n)->ll{
		__int128_t m=(ll)pow(n,0.125)+1;
		auto _gcd=[](__int128_t a,__int128_t b){
			while(a){
				b%=a;
				swap(a,b);
			}
			return b;
		};
		auto _abs=[](__int128_t x){return x<0?-x:x;};
		for(ll c=1;c<n;c++){
			auto f=[&](__int128_t x){return((x%n)*(x%n)+c)%n;};
			__int128_t y=0,r=1,q=1,g=1,k=0,x=0,ys=0;
			while(g==1){
				x=y;
				while(k<r*3/4){
					y=f(y);
					k++;
				}
				ll cnt=0;
				while(k<r&&g==1){
					ys=y;
					for(int i=0;i<min(m,r-k);i++){
						y=f(y);
						q=q*_abs(x-y)%n;
					}
					g=_gcd(q,n);
					k+=m;
				}
				k=r;
				r*=2;
			}
			if(g==n){
				g=1;
				y=ys;
				while(g==1){
					y=f(y);
					g=_gcd(_abs(x-y),n);
				}
			}
			if(g<n){
				if(primalityTest(g))return g;
				if(primalityTest(n/g))return n/g;
				return find_factor(find_factor,g);
			}
		}
		return 0;
	};

	map<ll,ll>mp;
	ll i=2;
	while(i*i<=n){
		ll k=0;
		while(n%i==0){
			n/=i;
			k++;
		}
		if(k)mp[i]=k;
		i+=i%2+1;
		if(i==101&&n>=(1ll<<20)){
			while(n>1){
				if(primalityTest(n)){
					mp[n]=1;
					n=1;
				}else{
					ll j=find_factor(find_factor,n);
					k=0;
					while(n%j==0){
						n/=j;
						k++;
					}
					mp[j]=k;
				}
			}
		}
	}
	if(n>1)mp[n]=1;
	vector<pair<ll,ll>>ret;
	for(auto p:mp)ret.push_back(p);
	sort(ret.begin(),ret.end());
	return ret;
}