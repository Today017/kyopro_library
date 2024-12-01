#include"../../kyopro_library/template.hpp"

template<typename T>
struct MergeSortTree{
	MergeSortTree()=default;
	MergeSortTree(const vector<T>&v){
		n=v.size();
		mx=*max_element(v.begin(),v.end()),mn=*min_element(v.begin(),v.end());
		dat=vector<vector<T>>(n<<1);
		for(int i=0;i<n;i++)dat[n+i]={a[i]};
		for(int i=n-1;i>0;i--){
			merge(
				dat[i<<1].begin(),dat[i<<1].end(),
				dat[i<<1|1].begin(),dat[i<<1|1].end(),
				back_inserter(dat[i]));
		}
	}

	int count_lt(int l,int r,T val){
		l+=n,r+=n;
		int ret=0;
		while(l<r){
			if(l&1)ret+=search(l++,val);
			if(r&1)ret+=search(--r,val);
			l>>=1,r>>=1;
		}
		return ret;
	}
	int count_le(int l,int r,T val){return count_lt(l,r,val+1);}
	int count_gt(int l,int r,T val){return n-l-count_le(l,r,val);}
	int count_ge(int l,int r,T val){return n-l-count_lt(l,r,val);}
	T kth(int l,int r,int k){
		T lo=mn-1,hi=mx+1;
		while(hi-lo>1){
			T mid=(hi+lo)/2;
			(count_lt(l,r,mid)>=k?hi:lo)=mid;
		}
		return lo;
	}

private:
	int n;
	vector<vector<T>>dat;
	int search(int i,T val){return lower_bound(dat[i].begin(),dat[i].end(),val)-dat[i].begin();}
	T mx,mn;
};


