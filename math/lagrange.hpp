#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/math/muleval.hpp"

//ラグランジュ補間
//n+1個の点(xi,yi)を通るn次多項式の係数を返す/O(n log^2 n)
template<typename T>
vector<T>lagrangePolynomial(vector<T>x,vector<T>y){
	int n=x.size();
	int n2=1;
	while(n2<n)n2<<=1;

	vector<vector<T>>g(n2*2,{1});
	for(int i=0;i<n;i++)g[n2+i]={-x[i],1};
	for(int i=n2-1;i>0;i--)g[i]=polyMul(g[i<<1],g[i<<1|1]);

	vector<T>prod=g[1];
	vector<T>diff=polyDifferential(prod),eval=multipointEvaluate(diff,x);

	using P=pair<vector<T>,vector<T>>;//first/second
	vector<P>g2(n2*2,{{0},{1}});
	for(int i=0;i<n;i++)g2[n2+i]={{y[i]},{-eval[i]*x[i],eval[i]}};
	auto merge=[](P l,P r)->P{
		vector<T>tmp1=polyMul(l.first,r.second),tmp2=polyMul(l.second,r.first);
		return{polyAdd(tmp1,tmp2),polyMul(l.second,r.second)};
	};
	for(int i=n2-1;i>0;i--)g2[i]=merge(g2[i<<1],g2[i<<1|1]);

	vector<T>ret=g2[1].first;
	T p=1;
	for(int i=0;i<n;i++)p*=eval[i];
	p=p.inv();
	for(int i=0;i<n;i++)ret[i]*=p;
	return ret;
}