#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief Suffix Array
/// sa[i] = j <-> s[j:] が辞書順 i 番目
// O(n log(n))
// ref: https://wk1080id.hatenablog.com/entry/2018/12/25/005926
template<int C=256>
vector<int> suffixArray(string s){
	s.push_back('$');
	int n=s.size();
	vector<int>p(n),c(n),cnt(max(n,C),0);
	//p[i] := 辞書順 i 番目のインデックス
	//c[i] := インデックス i の部分文字列の同値類

	//2^0,2^1,...,2^k,... をやる
	//k=0
	for(int i=0;i<n;i++)cnt[s[i]]++;
	for(int i=1;i<(int)cnt.size();i++)cnt[i]+=cnt[i-1];
	//辞書順 = 累積和の小さい順 になる
	for(int i=0;i<n;i++)p[--cnt[s[i]]]=i;
	//同値類を計算する
	c[p[0]]=0;
	for(int i=1;i<n;i++){
		c[p[i]]=c[p[i-1]];
		if(s[p[i]]!=s[p[i-1]])c[p[i]]++;
	}

	vector<int>np(n),nc(n);
	for(int k=0;(1<<k)<n;k++){
		//k を使って、(c[i],c[i+2^k]) でソート、 p[i]-=2^k でできる
		//c[i+2^k] でソート
		for(int i=0;i<n;i++)np[i]=p[i]-(1<<k),(np[i]+=n)%=n;
		fill(cnt.begin(),cnt.end(),0);
		for(int i=0;i<n;i++)cnt[c[np[i]]]++;
		for(int i=1;i<(int)cnt.size();i++)cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)p[--cnt[c[np[i]]]]=np[i];
		//同値類
		nc[p[0]]=0;
		for(int i=1;i<n;i++){
			nc[p[i]]=nc[p[i-1]];
			if(c[p[i]]!=c[p[i-1]]||c[(p[i]+(1<<k))%n]!=c[(p[i-1]+(1<<k))%n])nc[p[i]]++;
		}
		swap(c,nc);
	}

	p.erase(p.begin());
	return p;
}