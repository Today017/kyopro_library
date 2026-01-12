#include"../../kyopro_library/template.hpp"

///@brief マージソート木
template<typename T>
struct MergeSortTree {
    MergeSortTree()=default;

    ///@brief 配列 v からマージソート木を構築する
    MergeSortTree(const vector<T>& v) {
        n=v.size();
        mx=*max_element(ALL(v)); mn=*min_element(ALL(v));
        dat=vector<vector<T>>(n<<1);
        rep(i,n) dat[n+i]={v[i]};
        for(int i=n-1; i>0; i--) merge(all(dat[i<<1]),all(dat[i<<1|1]),back_inserter(dat[i]));
    }

    ///@brief 区間 [l, r) に存在する val 未満の値の個数を返す
    ///@note O(log(N)^2)
    int count_lt(int l, int r, T val) {
        l+=n; r+=n;
        int ret=0;
        while(l<r) {
            if(l&1) ret+=LB(dat[l],val), l++;
            if(r&1) --r, ret+=LB(dat[r],val);
            l>>=1; r>>=1;
        }
        return ret;
    }

    ///@brief 区間 [l, r) に存在する val 以下の値の個数を返す
    ///@note O(log(N)^2)
    int count_le(int l, int r, T val) {
        return count_lt(l,r,val+1);
    }

    ///@brief 区間 [l, r) に存在する val より大きい値の個数を返す
    ///@note O(log(N)^2)
    int count_gt(int l, int r, T val) {
        return r-l-count_le(l,r,val);
    }

    ///@brief 区間 [l, r) に存在する val 以上の値の個数を返す
    ///@note O(log(N)^2)
    int count_ge(int l, int r, T val) {
        return r-l-count_lt(l,r,val);
    }

    ///@brief 区間 [l, r) の小さい方から k(1-indexed) 番目の値を返す
    ///@note O(log(N)^3)
    T kth(int l, int r, int k) {
        T lo=mn-1,hi=mx+1;
        while(hi-lo>1) {
            T mid=(hi+lo)/2;
            if(count_lt(l,r,mid)>=k) hi=mid;
            else lo=mid;
        }
        return lo;
    }

private:
    int n;
    vector<vector<T>> dat;
    T mx,mn;
};