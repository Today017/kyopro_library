#pragma once
//https://atcoder.jp/contests/practice2
#include "../../kyopro_library/template.hpp"

#include "../../kyopro_library/graph/dsu.hpp"

void acl_practice_a() {
    int N,Q; cin>>N>>Q;
    DSU dsu(N);
    while(Q--) {
        int t,u,v; cin>>t>>u>>v;

        if(t==0) dsu.merge(u,v);
        else cout<<dsu.same(u,v)<<'\n';
    }
}

#include "../../kyopro_library/data_structure/fenwick_tree.hpp"

void acl_practice_b() {
    int N,Q; cin>>N>>Q;
    vector<ll> A(N); rep(i,N) cin>>A[i];

    FenwickTree fen(N); rep(i,N) fen.add(i,A[i]);

    while(Q--) {
        int t; cin>>t;

        if(t==0) {
            int p,x; cin>>p>>x;
            fen.add(p,x);
        } else {
            int l,r; cin>>l>>r;
            cout<<fen.sum(l,r)<<'\n';
        }
    }
}

#include "../../kyopro_library/math/floor_sum.hpp"

void acl_practice_c() {
    int T; cin>>T;
    while(T--) {
        ll N,M,A,B; cin>>N>>M>>A>>B;
        cout<<FloorSum(N,M,A,B)<<'\n';
    }
}

#include "../../kyopro_library/graph/flow/max_flow.hpp"
#include "../../kyopro_library/others/grid.hpp"

void acl_practice_d() {
    int N,M; cin>>N>>M;
    vector<string> S(N);
    rep(i,N) cin>>S[i];

    MaxFlow mf(N*M+2);
    int source=N*M, sink=source+1;

    GridUtil gu(N,M);

    rep(i,N) rep(j,M) if(S[i][j]=='.') {
        if((i+j)%2==0) {
            mf.add_edge(source,gu(i,j),1);
            for(auto [ni,nj]: gu.around4(i,j)) if(S[ni][nj]=='.') mf.add_edge(gu(i,j),gu(ni,nj),1);
        } else {
            mf.add_edge(gu(i,j),sink,1);
        }
    }

    cout<<mf.flow(source,sink)<<endl;
    vector<vector<char>> ans(N,vector<char>(M,'.'));
    rep(i,N) rep(j,M) if(S[i][j]=='#') ans[i][j]='#';
    for(auto e: mf.get_edges()) {
        if(e.from==source || e.to==sink || e.flow==0) continue;
        auto [x1,y1]=gu(e.from);
        auto [x2,y2]=gu(e.to);
        if(x1==x2) {
            if(y1<y2) {
                ans[x1][y1]='>'; ans[x2][y2]='<';
            } else {
                ans[x1][y1]='<'; ans[x2][y2]='>';
            }
        } else {
            if(x1<x2) {
                ans[x1][y1]='v'; ans[x2][y2]='^';
            } else {
                ans[x1][y1]='^'; ans[x2][y2]='v';
            }
        }
    }

    rep(i,N) {
        rep(j,M) cout<<ans[i][j];
        cout<<endl;
    }
}
