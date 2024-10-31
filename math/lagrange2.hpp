#include"../../kyopro_library/template.hpp"

//ラグランジュ補間
//n+1個の点(xi,yi)を通るn次多項式の係数を返す/O(n^2)
template<typename T>
vector<T>lagrangePolynomial(vector<T>x,vector<T>y){
	int n=x.size()-1;
	for(int i=0;i<=n;i++){
		T t=1;
		for(int j=0;j<=n;j++){
			if(i!=j)t*=x[i]-x[j];
		}
		y[i]/=t;
	}
	//前計算 dp[i]:=(x-x0)*...*(x-xn)の x^i の係数
	vector<T>dp(n+2);
	dp[0]=1;
	for(T xi:x){
		for(int i=n+1;i>=0;i--){
			dp[i]*=-xi;
			if(i>0)dp[i]+=dp[i-1];
		}
	}
	//戻すDP
	vector<T>ret(n+1);
	for(int i=0;i<=n;i++){
		if(x[i]==T(0)){
			for(int j=0;j<=n;j++)ret[j]+=dp[j+1]*y[i];
		}else{
			T inv=x[i].inv();
			ret[0]+=-dp[0]*inv*y[i];
			T pre=-dp[0]*inv;
			for(int j=1;j<=n;j++){
				ret[j]+=-(dp[j]-pre)*inv*y[i];
				pre=-(dp[j]-pre)*inv;
			}
		}
	}
	return ret;
}