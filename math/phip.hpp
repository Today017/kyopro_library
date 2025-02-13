#include"../../kyopro_library/template.hpp"

// phi[0] ... phi[n] を前計算する O(n log(log(n)))
// phi[i] = i以下であって、iと互いに素な数の個数
// ref: https://qiita.com/drken/items/3beb679e54266f20ab63
// ref: https://manabitimes.jp/math/667
// 公式: phi[n] = n * Π(1-1/p) (pはnの素因数)
// 公式: phi[n]phi[m] = phi[nm] (nとmが互いに素)
// 公式: Σ(d|n)phi[d] = n
// 公式: a^phi(m) ≡ 1 (mod m) (aとmが互いに素)
vector<ll>totientTable(ll n){
	vector<ll>ret(n+1);
	iota(ret.begin(),ret.end(),0);
	for(ll i=2;i<=n;i++){
		if(ret[i]==i){
			for(ll j=i;j<=n;j+=i)ret[j]=ret[j]/i*(i-1);
		}
	}
	return ret;
}