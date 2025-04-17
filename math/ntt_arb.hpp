#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/mod/modint.hpp"
#include"../../kyopro_library/math/proot.hpp"

/// @brief NTT Friendly 素数用 NTT 構造体
template<ll MOD>
class NTT{
	using mint=ModInt<MOD>;
	int primitive_root,divide_max;
	vector<ModInt<MOD>>roots,inv_roots;
	vector<mint>ntt(vector<mint>a,bool inv=false){
		int n=a.size();
		int h=0;
		while((1<<h)<n)h++;
		for(int i=0;i<n;i++){
			int j=0;
			for(int k=0;k<h;k++)j|=(i>>k&1)<<(h-1-k);
			if(i<j)swap(a[i],a[j]);
		}
		for(int b=1,t=1;b<n;b<<=1,t++){
			mint w=1,base=inv?inv_roots[t]:roots[t];
			for(int j=0;j<b;j++){
				for(int k=0;k<n;k+=b*2){
					mint s=a[j+k];
					mint t=a[j+k+b]*w;
					a[j+k]=s+t;
					a[j+k+b]=s-t;
				}
				w*=base;
			}
		}
		if(inv){
			mint inv_n=mint(n).inv();
			for(int i=0;i<n;i++)a[i]*=inv_n;
		}
		return a;
	}

public:
	NTT(){
		assert(primalityTest(MOD));
		primitive_root=primitiveRoot(MOD);
		divide_max=0;
		ll n=MOD-1;
		while(n%2==0){
			n>>=1;
			divide_max++;
		}
		roots=vector<mint>(divide_max+1);
		inv_roots=vector<mint>(divide_max+1);
		roots[0]=inv_roots[0]=mint(1);
		for(int i=1;i<=divide_max;i++){
			roots[i]=mint(primitive_root).pow((MOD-1)/(1<<i));
			inv_roots[i]=roots[i].inv();
		}
	}
	/// @brief a, b の畳み込みを求める
	vector<mint>convolve(vector<mint>a,vector<mint>b){
		int n=1;
		while(n<(int)a.size()+(int)b.size()-1)n<<=1;
		vector<mint>fa(n),fb(n);
		for(int i=0;i<(int)a.size();i++)fa[i]=a[i];
		for(int i=0;i<(int)b.size();i++)fb[i]=b[i];
		fa=ntt(fa);
		fb=ntt(fb);
		for(int i=0;i<n;i++)fa[i]*=fb[i];
		fa=ntt(fa,true);
		vector<mint>ret(n);
		for(int i=0;i<n;i++)ret[i]=fa[i];
		while((int)ret.size()>(int)a.size()+(int)b.size()-1)ret.pop_back();
		return ret;
	}
};