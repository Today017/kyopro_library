#include"../kyopro_library/data_structure/fenwick_tree.hpp"
#include"../kyopro_library/data_structure/fenwick_tree_abel.hpp"
#include"../kyopro_library/data_structure/segtree.hpp"
#include"../kyopro_library/data_structure/segtree_lazy.hpp"
#include"../kyopro_library/data_structure/segtree_dual.hpp"
#include"../kyopro_library/graph/dsu.hpp"
#include"../kyopro_library/others/int128.hpp"
#include"../atcoder/modint"
#include"../atcoder/segtree"
#include"../atcoder/lazysegtree"
#include"../atcoder/fenwicktree"
#include"../atcoder/dsu"

ostream& operator<<(ostream& os, atcoder::modint998244353 a);
ostream& operator<<(ostream& os, atcoder::modint1000000007 a);
template<typename T, T(*op)(T,T), T(*e)()>
ostream& operator<<(ostream& os, atcoder::segtree<T,op,e> a);
template<typename T, T(*op)(T,T), T(*e)(), typename F, T(*mapping)(F,T), F(*composition)(F,F), F(*id)()>
ostream& operator<<(ostream& os, atcoder::lazy_segtree<T,op,e,F,mapping,composition,id> a);
template<typename T>
ostream& operator<<(ostream& os, atcoder::fenwick_tree<T> a);
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& p);
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3>& t);
template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3,T4>& t);
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<vector<T>>>& a);
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& a);
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& a);
template<typename T>
ostream& operator<<(ostream& os, const set<T>& a);
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& a);
template<typename T>
ostream& operator<<(ostream& os, const deque<T>& a);
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const map<T1,T2>& a);
template<typename T>
ostream& operator<<(ostream& os, queue<T> a);
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T> a);
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T,vector<T>,greater<T>> a);
template<typename T, auto N>
ostream& operator<<(ostream& os, array<T,N> a);
ostream& operator<<(ostream& os, FenwickTree a);
template<typename T>
ostream& operator<<(ostream& os, FenwickTreeAbel<T> a);
template<typename T>
ostream& operator<<(ostream& os, SegTree<T> a);
template<typename T, typename U, auto M>
ostream& operator<<(ostream& os, SegTreeLazy<T,U,M> a);
template<typename T>
ostream& operator<<(ostream& os, SegTreeDual<T> a);
ostream& operator<<(ostream& os, DSU a);
ostream& operator<<(ostream& os, atcoder::dsu a);

ostream& operator<<(ostream& os, atcoder::modint998244353 a) {
    os<<a.val();
    return os;
}
ostream& operator<<(ostream& os, atcoder::modint1000000007 a) {
    os<<a.val();
    return os;
}
template<typename T, T(*op)(T,T), T(*e)()>
ostream& operator<<(ostream& os, atcoder::segtree<T,op,e> a) {
    int n=a.get_size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a.prod(i,i+1);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T, T(*op)(T,T), T(*e)(), typename F, T(*mapping)(F,T), F(*composition)(F,F), F(*id)()>
ostream& operator<<(ostream& os, atcoder::lazy_segtree<T,op,e,F,mapping,composition,id> a) {
    int n=a.get_size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a.get(i);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, atcoder::fenwick_tree<T> a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a.sum(i,i+1);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const pair<T1,T2>& p) {
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3>& t) {
    os<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";
    return os;
}
template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream& os, const tuple<T1,T2,T3,T4>& t) {
    os<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<","<<get<3>(t)<<")";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<vector<T>>>& a) {
    int I=a.size();
    os<<"[\n";
    for(int i=0; i<I; i++) {
        os<<" "<<i<<":[\n";
        int J=a[i].size();
        for(int j=0; j<J; j++) {
            os<<"	 "<<j<<":[";
            int K=a[i][j].size();
            for(int k=0; k<K; k++) {
                os<<a[i][j][k];
                if(k!=K-1) os<<",";
            }
            os<<"]\n";
        }
        os<<" ]\n";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& a) {
    os<<"[\n";
    int I=a.size();
    for(int i=0; i<I; i++) {
        os<<" "<<i<<":[";
        int J=a[i].size();
        for(int j=0; j<J; j++) {
            os<<a[i][j];
            if(j!=J-1) os<<",";
        }
        os<<"]\n";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const set<T>& a) {
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const multiset<T>& a) {
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const deque<T>& a) {
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T1, typename T2>
ostream& operator<<(ostream& os, const map<T1,T2>& a) {
    os<<"[";
    for(pair<T1,T2> x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, queue<T> a) {
    int n=a.size();
    os<<"[";
    while(!a.empty()) {
        os<<a.front()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T> a) {
    int n=a.size();
    os<<"[";
    while(!a.empty()) {
        os<<a.top()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, priority_queue<T,vector<T>,greater<T>> a) {
    os<<"[";
    while(!a.empty()) {
        os<<a.top()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T, auto N>
ostream& operator<<(ostream& os, array<T,N> a) {
    os<<"[";
    for(int i=0; i<N; i++) {
        os<<a[i];
        if(i!=N-1) os<<",";
    }
    os<<"]";
    return os;
}
ostream& operator<<(ostream& os, FenwickTree a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, FenwickTreeAbel<T> a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, SegTree<T> a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T, typename U, auto M>
ostream& operator<<(ostream& os, SegTreeLazy<T,U,M> a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, SegTreeDual<T> a) {
    int n=a.size();
    os<<"[";
    for(int i=0; i<n; i++) {
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
ostream& operator<<(ostream& os, DSU a) {
    vector<vector<int>> group=a.groups();
    os<<group;
    return os;
}
ostream& operator<<(ostream& os, atcoder::dsu a) {
    vector<vector<int>> group=a.groups();
    os<<group;
    return os;
}

#define print_line cerr<<"--------------------"<<__LINE__<<"--------------------"<<endl;
#define debug(...) DebugPrint(0,#__VA_ARGS__,__VA_ARGS__)
#define getName(VariableName) #VariableName

template<typename T>
void DebugPrint(int i, T name) { cerr<<endl; }
template<typename T1, typename T2, typename...T3>
void DebugPrint(int i, const T1& name, const T2& a, const T3& ...b) {
    cerr<<"\033[31m";
    int tmp=0;
    while(true) {
        if(name[i]=='\0') break;
        if(tmp==0&&name[i]==',') break;
        cerr<<name[i];
        if(name[i]=='(') tmp++;
        else if(name[i]==')') tmp--;
        i++;
    }
    cerr<<"\033[32m";
    cerr<<":"<<a<<",";
    cerr<<"\033[0m";
    DebugPrint(i+1,name,b...);
}
