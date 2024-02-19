#include <bits/stdc++.h>
using namespace std;

namespace random_generator{
    using ll=long long;
    mt19937_64 generate;
    void init(){
        random_device seed_gen;
        generate=mt19937_64(seed_gen());
    }
    struct dsu {
        dsu(int n) {
            par = vector<int>(n);
            sz = vector<int>(n);
            for (int i = 0; i < n; i++) {
                par[i] = i;
                sz[i] = 1;
            }
        }
        int find(int x) {
            if (par[x] == x) return x;
            par[x] = find(par[x]);
            return par[x];
        }
        void unite(int x, int y) {
            x = find(x);
            y = find(y);
            if (x == y) return;
            if (sz[x] < sz[y]) swap(x, y);
            par[y] = x;
            sz[x] += sz[y];
        }
        int size(int x) {
            return sz[find(x)];
        }
        bool is_united(int x, int y) {
            return find(x) == find(y);
        }

    private:
        vector<int> par, sz;
    };
    ll randll(ll x){
        assert(x>0);
        return generate()%x;
    }
    // [x,y)
    ll randll(ll x, ll y){
        assert(x<y);
        return x+generate()%(y-x);
    }
    ll get_elem(vector<ll>&a){
        const int n=a.size();
        int idx=randll(0,n);
        swap(a[n-1],a[idx]);
        int ret=a.back();
        a.pop_back();
        return ret;
    }
    // ランダムな数列
    // [lo,hi)
    // no_dup:重複無しか有りか
    vector<ll> random_seq(int n, ll lo, ll hi, bool no_dup=false){
        vector<ll>ret(n);
        if(!no_dup){
            for(int i=0;i<n;i++){
                ret[i]=randll(lo,hi);
            }
        }
        else{
            set<ll>st;
            for(int i=0;i<n;i++){
                int r=randll(lo,hi);
                while(st.count(r))r=randll(lo,hi);
                ret[i]=r;
                st.insert(r);
            }
        }
        return ret;
    }
    // ランダムな文字列(アルファベットのみ)
    // lower:lowercase
    string random_alphabet(int n, bool lower=true){
        string ret;
        for(int i=0;i<n;i++){
            int idx=randll(26);
            ret.push_back(char((lower?'a':'A')+idx));
        }
        return ret;
    }
    // ランダムな文字列(sの要素からなる)
    string random_string(int n, string s){
        string ret;
        int m=s.size();
        for(int i=0;i<n;i++){
            int idx=randll(m);
            ret.push_back(s[idx]);
        }
        return ret;
    }
    // ランダムな行列
    vector<vector<ll>> random_seq_2D(int h, int w, ll lo, ll hi){
        vector<vector<ll>>ret(h,vector<ll>(w));
        for(int i=0;i<h;i++){
            ret[i]=random_seq(w, lo, hi);
        }
        return ret;
    }
    // ランダムな文字列の列(アルファベットのみ)
    vector<string> random_alphabet_2D(int h, int w, bool lower=true){
        vector<string>ret(h);
        for(int i=0;i<h;i++)ret[i]=random_alphabet(w, lower);
        return ret;
    }
    // ランダムな木
    vector<pair<int,int>> random_tree(int n){
        vector<ll>a=random_seq(n-2,1,n+1);
        vector<int>d(n+1);
        for(int i=0;i<n-2;i++)d[a[i]]++;
        for(int i=1;i<=n;i++)d[i]++;
        vector<pair<int,int>>ret;
        set<int>pq;
        for(int i=1;i<=n;i++){
            if(d[i]==1)pq.insert(i);
        }
        for(int i=0;i<n-2;i++){
            int v=(*pq.begin());
            pq.erase(v);
            ret.push_back(make_pair(v,a[i]));
            d[v]--;
            d[a[i]]--;
            if(d[a[i]]==1){
                pq.insert(a[i]);
            }else if(d[a[i]]==0){
                pq.erase(a[i]);
            }
        }
        for(int i=1;i<=n;i++){
            if(d[i]==1){
                for(int j=i+1;j<=n;j++){
                    if(d[j]==1){
                        ret.push_back(make_pair(i,j));
                        break;
                    }
                }
                break;
            }
        }
        return ret;
    }
    // ランダムな完全二分木
    vector<pair<int,int>>random_bintree(int n){
        vector<pair<int,int>>ret;
        vector<ll>roots={randll(1,n+1)};
        vector<ll>leaves;
        for(int i=1;i<=n;i++){
            if(i!=roots.back()){
                leaves.push_back(i);
            }
        }
        while(!leaves.empty()){
            int root=get_elem(roots);
            int leaf=get_elem(leaves);
            ret.push_back(make_pair(root,leaf));
            roots.push_back(leaf);
            if(!leaves.empty()){
                int leaf=get_elem(leaves);
                ret.push_back(make_pair(root,leaf));
                roots.push_back(leaf);
            }
        }
        return ret;
    }
    // ランダムな無向グラフ
    vector<pair<int,int>>random_undigraph(int n, int m, bool connected=true){
        vector<pair<int,int>>edges;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                edges.push_back(make_pair(i+1,j+1));
            }
        }
        int ed=edges.size();
        if(!connected){
            vector<pair<int,int>> ret;
            vector<ll>idxs=random_seq(m,0,ed,true);
            for(int idx:idxs){
                ret.push_back(edges[idx]);
            }
            return ret;
        }
        else{
            vector<pair<int,int>>ret;
            while(true){
                ret.clear();
                vector<ll>idxs=random_seq(m,0,ed,true);
                dsu ds(n);
                for(int idx:idxs){
                    ret.push_back(edges[idx]);
                    auto [a,b]=edges[idx];
                    ds.unite(--a,--b);
                }
                bool ok=true;
                for(int i=0;i<n;i++){
                    ok&=ds.find(i)==ds.find(0);
                }
                if(ok)return ret;
            }
        }
    }
};
