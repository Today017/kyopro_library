#include"../kyopro_library/template.hpp"
namespace Util {
    using vi=vector<int>; using vvi=vector<vi>;
    using vl=vector<ll>; using vvl=vector<vl>;
    using pi=pair<int,int>; using vpi=vector<pi>;
    using pl=pair<ll,ll>; using vpl=vector<pl>;
    using vst=vector<string>;
    using weigraph=vector<vector<pair<int,ll>>>;
    using ull=unsigned long long; using ld=long double; using lll=__int128_t;
    template<typename T>
    using max_pq=priority_queue<T>;
    template<typename T>
    using min_pq=priority_queue<T,vector<T>,greater<T>>;

    auto Min(const auto& v) { return *min_element(all(v)); }
    auto Max(const auto& v) { return *max_element(all(v)); }
    auto Sum(const auto& v) { return reduce(all(v)); }
    int Lob(const auto& v, const auto& x) { return lower_bound(all(v),x)-v.begin(); }
    void Uniq(auto& v) { sort(all(v)); v.erase(unique(all(v)),v.end()); }
    void Inc(auto& a) { for(auto& x: a) x++; }
    void Dec(auto& a) { for(auto& x: a) x--; }
    #define each(a,v) for(auto&& a: v)

    const string YesNo(bool f) { return f?"Yes":"No"; }
    const string YESNO(bool f) { return f?"YES":"NO"; }
    const char NL='\n';
    #define Exout(x) { cout<<(x)<<NL; return; }

    template<typename T>
    istream& operator>>(istream& is, vector<vector<T>>& v) { for(auto& x: v) for(auto& y: x) is>>y; return is; }
    template<typename T>
    istream& operator>>(istream& is, vector<T>& v) { for(auto& x: v) is>>x; return is; }
    template<typename T1, typename T2>
    istream& operator>>(istream& is, pair<T1,T2>& p) { is>>p.first>>p.second; return is; }

    template<typename... T>
    void Read(T&... args) { (cin>>...>>args); }
    #define INT(...) int __VA_ARGS__; Util::Read(__VA_ARGS__);
    #define LL(...) ll __VA_ARGS__; Util::Read(__VA_ARGS__);
    #define STR(...) string __VA_ARGS__; Util::Read(__VA_ARGS__);
    #define VI(A,N) vector<int> A(N); Util::Read(A);
    #define VVI(A,N,M) vector<vector<int>> A(N,vector<int>(M)); Util::Read(A);
    #define VL(A,N) vector<ll> A(N); Util::Read(A);
    #define VVL(A,N,M) vector<vector<ll>> A(N,vector<ll>(M)); Util::Read(A);
    #define VI2(A,B,N) vector<int> A(N),B(N); rep(i,N) cin>>A[i]>>B[i];
    #define VL2(A,B,N) vector<ll> A(N),B(N); rep(i,N) cin>>A[i]>>B[i];
    #define VST(A,N) vector<string> A(N); Util::Read(A);

    void WriteVec(const auto& v) {
        for(const auto& x: v) cout<<x<<' ';
        cout<<NL;
    }

    vvi ReadGraph(int N, int M, bool directed=false, bool one_indexed=true) {
        vvi G(N);
        rep(i,M) {
            INT(a,b);
            if(one_indexed) a--, b--;
            G[a].push_back(b);
            if(!directed) G[b].push_back(a);
        }
        return G;
    }

    weigraph ReadWGraph(int N, int M, bool directed=false, int one_indexed=true) {
        weigraph G(N);
        rep(i,M) {
            INT(a,b); LL(c);
            if(one_indexed) a--, b--;
            G[a].push_back({b,c});
            if(!directed) G[b].push_back({a,c});
        }
        return G;
    }

    const vector<int> DX={1,0,-1,0,1,-1,-1,1};
    const vector<int> DY={0,1,0,-1,1,1,-1,-1};
    bool InRange(int l, int r, int x) { return l<=x && x<r; }

    template<typename T>
    vector<T> Inv(const vector<T>& v) {
        vector<T> ret(v.size());
        rep(i,v.size()) ret[v[i]]=i;
        return ret;
    }

    template<typename T>
    vector<int> Count(const vector<T>& v) {
        vector<int> ret(Max(v)+1);
        for(const auto& x: v) ret[x]++;
        return ret;
    }

    template<typename T>
    map<T,vector<int>> CountIdx(const vector<T>& v) {
        map<T,vector<int>> ret;
        rep(i,v.size()) ret[v[i]].push_back(i);
        return ret;
    }

    template<typename T>
    vector<vector<T>> Rotate90(const vector<vector<T>>& v) {
        int N=v.size(), M=v[0].size();
        vector<vector<T>> ret(M, vector<T>(N));
        rep(i,N) rep(j,M) ret[j][N-1-i]=v[i][j];
        return ret;
    }

    template<typename T>
    vector<ll> PrefixSum(const vector<T>& v) {
        int N=v.size();
        vector<ll> ret(N+1);
        rep(i,N) ret[i+1]=ret[i]+v[i];
        return ret;
    }

    int Digit(ll n) { int ret=0; while(n) ret++, n/=10; return ret; }
    ll Ten(int r) { ll ret=1; while(r--) ret*=10; return ret; }
    ll IntPow(ll x, ll r) { ll ret=1; while(r--) ret*=x; return ret; }
}
using namespace Util;
