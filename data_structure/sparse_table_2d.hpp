#include"../../kyopro_library/template.hpp"

struct{
	int h,w;
	ll sign;
	ll dat[12][12][1010][1010];
	ll log_table[5050];
}SparseTable2D;

void SparseTable2DInit(const vector<vector<ll>>&a,bool is_min=true){
	if(!is_min){
		SparseTable2D.sign=-1;
	}
	SparseTable2D.h=a.size();
	SparseTable2D.w=a[0].size();
	for(int i=0;i<SparseTable2D.h;i++){
		for(int j=0;j<SparseTable2D.w;j++){
			SparseTable2D.dat[0][0][i][j]=SparseTable2D.sign*a[i][j];
		}
	}
	for(int i=2;i<=max(SparseTable2D.h,SparseTable2D.w);i++){
		SparseTable2D.log_table[i]=SparseTable2D.log_table[i/2]+1;
	}
	for(int k=1;(1<<k)<=SparseTable2D.h;k++){
		for(int i=0;i+(1<<k)<=SparseTable2D.h;i++){
			for(int j=0;j<SparseTable2D.w;j++){
				SparseTable2D.dat[k][0][i][j]=min(SparseTable2D.dat[k-1][0][i][j],SparseTable2D.dat[k-1][0][i+(1<<(k-1))][j]);
			}
		}
	}
	for(int k=0;(1<<k)<=SparseTable2D.h;k++){
		for(int l=1;(1<<l)<=SparseTable2D.w;l++){
			for(int i=0;i+(1<<k)<=SparseTable2D.h;i++){
				for(int j=0;j+(1<<l)<=SparseTable2D.w;j++){
					SparseTable2D.dat[k][l][i][j]=min(SparseTable2D.dat[k][l-1][i][j],SparseTable2D.dat[k][l-1][i][j+(1<<(l-1))]);
				}
			}
		}
	}
}

ll SparseTable2DQuery(int l,int r,int u,int d){
	int i=SparseTable2D.log_table[r-l];
	int j=SparseTable2D.log_table[d-u];
	return min({SparseTable2D.dat[i][j][l][u],SparseTable2D.dat[i][j][r-(1<<i)][u],SparseTable2D.dat[i][j][l][d-(1<<j)],SparseTable2D.dat[i][j][r-(1<<i)][d-(1<<j)]})*SparseTable2D.sign;
}