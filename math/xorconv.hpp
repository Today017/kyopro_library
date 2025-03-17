#include "../../kyopro_library/template.hpp"

template<typename T>
vector<T> FHT(vector<T> a,bool inv=false){
	int h=__lg(n);
	for(int i=0;i<h;i++){
		for(int j=0;j<1<<h;j++){
			if(~j>>i){
				T x=a[j],y=a[j|1<<i];
				a[j]=x+y,a[j|1<<i]=x-y;
				if(inv)a[j]>>=1,a[j|1<<i]>>=1;
			}
		}
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
