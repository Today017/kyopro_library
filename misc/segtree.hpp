struct SegTree {
    using T=hoge;
    T op(T a, T b) {
        return max(a,b);
    }
    T id() {
        return INF;
    }

    int n;
    vector<T> dat;
    SegTree(int n): n(n), dat(2*n,id()) {}

    void set(int i, int x) {
        i+=n;
        dat[i]=x;
        while(i>>=1) dat[i]=op(dat[i<<1],dat[i<<1|1]);
    }

    T fold(int l, int r) {
        l+=n; r+=n;
        T ret=id();
        while(l<r) {
            if(l&1) ret=op(ret,dat[l++]);
            if(r&1) ret=op(ret,dat[--r]);
            l>>=1; r>>=1;
        }
        return ret;
    }
};
