#include"../../kyopro_library/template.hpp"

/*
	F_2 上の連立線形方程式
	ref:https://mathlandscape.com/solution-sp/
	ref:https://yukicoder.me/submissions/1011997
	verify:https://yukicoder.me/problems/no/2895
*/

//掃き出し法
//vector<vector<bool>>a:連立方程式 Ax=b の拡大係数行列
//vector<int>where:ピボットとなる変数を記録するための配列
//return:a のランク
int rowReduction(vector<vector<bool>>&a,vector<int>&where){
	int row=a.size(),col=a.front().size();
	int rank=0;
	for(int c=0;c<col-1;c++){
		int pivot=rank;
		while(pivot<row&&!a[pivot][c])pivot++;
		if(pivot==row)continue;
		swap(a[pivot],a[rank]);
		where.push_back(c);
		for(int r=0;r<row;r++){
			if(r!=rank&&a[r][c]){
				//A[r]^=A[c]
				for(int i=0;i<col;i++)a[r][i]=a[r][i]^a[rank][i];
			}
		}
		rank++;
	}
	return rank;
}

//連立線形方程式 Ax=b を解く
//x0:特殊解(b=0 の場合は自明解になる)
//ker:Ax=0 の解空間の基底
//一般解は x0 と解空間の基底の任意の線形結合で表される
//A のサイズによっては基底のサイズが巨大になるので注意すること
bool linearEquation(vector<vector<bool>>a,vector<bool>b,vector<bool>&x0,vector<vector<bool>>&ker){
	int row=a.size(),col=a.front().size();
	assert(b.size()==row);
	vector<vector<bool>>a2=a;
	for(int i=0;i<row;i++)a2[i].push_back(b[i]);

	vector<int>where;
	int rank=rowReduction(a2,where);

	for(int r=rank;r<row;r++){
		if(a2[r].back())return false;
	}

	x0=vector<bool>(col,false);
	for(int i=0;i<rank;i++)x0[where[i]]=a2[i].back();

	int r=0;
	for(int c=0;c<col;c++){
		if(r<rank&&c==where[r]){
			r++;
			continue;
		}
		vector<bool>x(col);
		x[c]=true;
		for(int r2=0;r2<r;r2++)x[where[r2]]=a2[r2][c];
		ker.push_back(x);
	}

	return rank;
}