#include"../kyopro_library/data_structure/fenwick_tree.hpp"
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

ostream& operator<<(ostream &os, atcoder::modint998244353 a){
    os<<a.val();
    return os;
}
ostream& operator<<(ostream &os, atcoder::modint1000000007 a){
    os<<a.val();
    return os;
}
template<typename T, T(*op)(T,T), T(*e)()>
ostream& operator<<(ostream &os, atcoder::segtree<T,op,e> a){
    int n=a.get_size();
    os<<"[";
    REP(i,n){
        os<<a.prod(i,i+1);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T, T(*op)(T,T), T(*e)(), typename F, T(*mapping)(F,T), F(*composition)(F,F), F(*id)()>
ostream& operator<<(ostream &os, atcoder::lazy_segtree<T,op,e,F,mapping,composition,id> a){
    int n=a.get_size();
    os<<"[";
    REP(i,n){
        os<<a.get(i);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, atcoder::fenwick_tree<T> a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a.sum(i,i+1);
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T1, typename T2>
ostream& operator<<(ostream &os, const pair<T1,T2> &p){
    os<<"("<<p.first<<","<<p.second<<")";
    return os;
}
template<typename T1, typename T2, typename T3>
ostream& operator<<(ostream &os, const tuple<T1,T2,T3> &t){
    os<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<")";
    return os;
}
template<typename T1, typename T2, typename T3, typename T4>
ostream& operator<<(ostream &os, const tuple<T1,T2,T3,T4> &t){
    os<<"("<<get<0>(t)<<","<<get<1>(t)<<","<<get<2>(t)<<","<<get<3>(t)<<")";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, const vector<vector<vector<T>>> &a){
    int I=a.size();
    os<<"[\n";
    REP(i,I){
        os<<" "<<i<<":[\n";
        int J=a[i].size();
        REP(j,J){
            os<<"	 "<<j<<":[";
            int K=a[i][j].size();
            REP(k,K){
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
ostream& operator<<(ostream &os, const vector<vector<T>> &a){
    os<<"[\n";
    int I=a.size();
    REP(i,I){
        os<<" "<<i<<":[";
        int J=a[i].size();
        REP(j,J){
            os<<a[i][j];
            if(j!=J-1) os<<",";
        }
        os<<"]\n";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, const vector<T> &a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, const set<T> &a){
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, const multiset<T> &a){
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, const deque<T> &a){
    int n=a.size();
    os<<"[";
    for(T x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T1, typename T2>
ostream& operator<<(ostream &os, const map<T1,T2> &a){
    os<<"[";
    for(pair<T1,T2> x:a) os<<x<<",";
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, queue<T> a){
    int n=a.size();
    os<<"[";
    while(!a.empty()){
        os<<a.front()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, priority_queue<T> a){
    int n=a.size();
    os<<"[";
    while(!a.empty()){
        os<<a.top()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, rpriority_queue<T> a){
    int n=a.size();
    os<<"[";
    while(!a.empty()){
        os<<a.top()<<",";
        a.pop();
    }
    os<<"]";
    return os;
}
template<typename T, auto N>
ostream& operator<<(ostream &os, array<T,N> a){
    os<<"[";
    REP(i,N){
        os<<a[i];
        if(i!=N-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, FenwickTree<T> a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, SegTree<T> a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T, typename U, auto M>
ostream& operator<<(ostream &os, SegTreeLazy<T,U,M> a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
template<typename T>
ostream& operator<<(ostream &os, SegTreeDual<T> a){
    int n=a.size();
    os<<"[";
    REP(i,n){
        os<<a[i];
        if(i!=n-1) os<<",";
    }
    os<<"]";
    return os;
}
ostream& operator<<(ostream &os, DSU a){
    VVI group=a.groups();
    os<<group;
    return os;
}
ostream& operator<<(ostream&os, atcoder::dsu a){
    VVI group=a.groups();
    os<<group;
    return os;
}

#define print_line cerr<<"--------------------"<<__LINE__<<"--------------------"<<"\n"
#define debug(...) debugPrint(0,#__VA_ARGS__,__VA_ARGS__)
#define getName(VariableName) #VariableName

template<typename T>
void debugPrint(int i, T name){ cerr<<endl; }
template<typename T1, typename T2, typename...T3>
void debugPrint(int i, const T1 &name, const T2 &a, const T3 &...b){
    cerr<<"\033[31m";
    int tmp=0;
    while(true){
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
    debugPrint(i+1,name,b...);
}