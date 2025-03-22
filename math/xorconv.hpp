#include "../../kyopro_library/template.hpp"

// 高速アダマール変換
template<typename T>
vector<T> FHT(vector<T> a,bool inv=false){
	int h=__lg(a.size());
	for(int i=0;i<h;i++){
		for(int j=0;j<1<<h;j++){
			if(~j>>i&1){
				T x=a[j],y=a[j|1<<i];
				a[j]=x+y,a[j|1<<i]=x-y;
				if(inv)a[j]/=2,a[j|1<<i]/=2;
			}
		}
	}
	return a;
}

//XOR Convolution
//C[k] = Σ(i^j = k) A[i]B[j] なる C を返す
template<typename T>
vector<T> xorConvolution(vector<T>a,vector<T>b){
	a=FHT(a),b=FHT(b);
	for(int i=0;i<(int)a.size();i++)a[i]*=b[i];
	a=FHT(a,true);
	return a;
}
