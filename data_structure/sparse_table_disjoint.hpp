#include "../../kyopro_library/template.hpp"

/// @brief Disjoint Sparse Table
/// @tparam Semigroup 半群（結合則が成り立つこと）
template<typename Semigroup>
struct SparseTableDisjoint{
	using Type=typename Semigroup::Type;
	SparseTableDisjoint()=default;

	/// @brief 配列 v からDisjoint Sparse Tableを構築する
	/// @note O(N log(N))
	SparseTableDisjoint(const vector<Type>&v){
		n=v.size();
		dat.assign(__lg(n)+1,vector<Type>(n));
		dat[0]=v;
		for(int i=1;i<(int)dat.size();i++){
			int w=1<<i;
			for(int j=0;j<n;j+=w<<1){
				int t=min(j+w,n);
				dat[i][t-1]=v[t-1];
				for(int k=t-2;k>=j;k--)dat[i][k]=Semigroup::op(v[k],dat[i][k+1]);
				if(t>=n)break;
				dat[i][t]=v[t];
				for(int k=t+1;k<min(j+(w<<1),n);k++)dat[i][k]=Semigroup::op(dat[i][k-1],v[k]);
			}
		}
	}

	/// @brief 区間 [l, r) の半群積を返す
	/// @note O(1)
	Type fold(int l,int r){
		r--;
		if(l==r)return dat[0][l];
		int i=__lg(l^r);
		return Semigroup::op(dat[i][l],dat[i][r]);
	}

	/// @brief i 番目の要素を返す
	Type operator[](int i)const{return fold(i,i+1);}

	/// @brief 配列のサイズを返す
	int size(){return n;}

private:
	int n;
	vector<vector<Type>>dat;
};