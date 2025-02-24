#pragma once
#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/string/sa.hpp"

//LCP Array
//lcp[i] := sa[i] と sa[i-1] の lcp の長さ
//ref: https://qiita.com/kgoto/items/9e28e37b8a4b15ea7230
vector<int> lcpArray(const string &s,const vector<int>&sa){
	int n=s.size();
	vector<int>lcp(n-1),rank(n);
	for(int i=0;i<n;i++)rank[sa[i]]=i;

	int len=0;//lcp の長さ
	for(int i=0;i<n;i++){
		if(rank[i]==0)continue;
		int j=sa[rank[i]-1];

		while(i+len<n&&j+len<n&&s[i+len]==s[j+len])len++;
		lcp[rank[i]-1]=len;

		if(len>0)len--;
	}

	return lcp;
}