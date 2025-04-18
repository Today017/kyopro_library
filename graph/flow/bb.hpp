#include"../../../kyopro_library/template.hpp"

//燃やす埋める
#include<atcoder/maxflow>
template<typename Cost>
struct BurningBurying{
	int n,start,goal;
	Cost offset=0;
	atcoder::mf_graph<Cost> mf;
	BurningBurying(int n){
		this->n=n;
		start=n;
		goal=n+1;
		mf=atcoder::mf_graph<Cost>(n+2);
	}
	//0,1
	void add_single(int i,Cost zero,Cost one){
		if(zero<=one){
			//基本コストがzeroで、iを0から1に変えると+one-zeroされる
			offset+=zero;
			mf.add_edge(start,i,one-zero);
		}else{
			//基本コストがoneで、iを1から0に変えると-one+zeroされる
			offset+=one;
			mf.add_edge(i,goal,zero-one);
		}
	}
	//(0,0),(0,1),(1,0),(1,1)
	void add_double(int i,int j,Cost a,Cost b,Cost c,Cost d){
		assert(b+c>=a+d);
		offset+=a;
		add_single(i,0,c-a);
		add_single(j,0,d-c);
		mf.add_edge(i,j,b+c-a-d);
	}
	Cost solve(){return mf.flow(start,goal)+offset;}
};
