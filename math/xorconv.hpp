#include "../../kyopro_library/template.hpp"

template<typename T>
vector<T> FHT(vector<T> a,bool inv=false){
	int n=a.size();
	for(int b=1;b<n;b<<=1){
		for(int j=0;j<n;j++){
			if((j&b)==0){
				T x=a[j],y=a[j|b];
				a[j]=x+y;
				a[j|b]=x-y;
			}
		}
	}
	if(inv){
		for(int i=0;i<n;i++)a[i]/=n;
	}
	return a;
}

template<typename T>
vector<T> xorConvolution(const vector<T>&a,const vector<T>&b){
	int n=1;
	while(n<(int)a.size()+(int)b.size()-1)n*=2;
	vector<T>fa(n),fb(n);
	for(int i=0;i<(int)a.size();i++)fa[i]=a[i];
	for(int i=0;i<(int)b.size();i++)fb[i]=b[i];
	fa=FHT(fa),fb=FHT(fb);
	for(int i=0;i<n;i++)fa[i]*=fb[i];
	fa=FHT(fa,true);
	return fa;
}