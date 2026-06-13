#pragma once
#include"../../kyopro_library/template.hpp"

///@brief グリッド操作用関数
struct GridUtil {
    const vi dx={0,1,0,-1,1,1,-1,-1};
    const vi dy={1,0,-1,0,1,-1,1,-1};

    int H,W;
    GridUtil(int H, int W): H(H),W(W) {}

    int index(int x, int y) { return x*W+y; }
    pair<int,int> pos(int idx) { return {idx/W, idx%W}; }
    bool in(int x, int y) { return 0<=x && x<H && 0<=y && y<W; }

    vector<pair<int,int>> around4(int x, int y) {
        vector<pair<int,int>> ret;
        rep(i,4) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vector<pair<int,int>> around2(int x, int y) {
        vector<pair<int,int>> ret;
        rep(i,2) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vector<pair<int,int>> around8(int x, int y) {
        vector<pair<int,int>> ret;
        rep(i,8) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vi around4(int i) {
        vi ret;
        int x=i/W, y=i%W;
        rep(j,4) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    vi around2(int i) {
        vi ret;
        int x=i/W, y=i%W;
        rep(j,2) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    vi around8(int i) {
        vi ret;
        int x=i/W, y=i%W;
        rep(j,8) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    bool is_even(int x, int y) { return (x+y)%2==0; }

    pair<int,int> operator()(int i) { return pos(i); }
    int operator()(int i, int j) { return index(i,j); }
};
