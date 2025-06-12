#include"../../kyopro_library/template.hpp"

/// @brief グリッド操作用関数
struct GridUtil {
    const vector<int> dx={0,1,0,-1,1,1,-1,-1};
    const vector<int> dy={1,0,-1,0,1,-1,1,-1};

    int h,w;
    GridUtil(int h, int w): h(h),w(w) {}

    int index(int x, int y) { return x*w+y; }
    pair<int,int> pos(int idx) { return {idx/w, idx%w}; }
    bool in(int x, int y) { return 0<=x && x<h && 0<=y && y<w; }

    vector<pair<int,int>> around4(int x, int y) {
        vector<pair<int,int>> ret;
        for(int i=0; i<4; i++) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vector<pair<int,int>> around2(int x, int y) {
        vector<pair<int,int>> ret;
        for(int i=0; i<2; i++) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vector<pair<int,int>> around8(int x, int y) {
        vector<pair<int,int>> ret;
        for(int i=0; i<8; i++) {
            int nx=x+dx[i], ny=y+dy[i];
            if(in(nx,ny)) ret.push_back({nx,ny});
        }
        return ret;
    }

    vector<int> around4(int i) {
        vector<int> ret;
        int x=i/w, y=i%w;
        for(int j=0; j<4; j++) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    vector<int> around2(int i) {
        vector<int> ret;
        int x=i/w, y=i%w;
        for(int j=0; j<2; j++) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    vector<int> around8(int i) {
        vector<int> ret;
        int x=i/w, y=i%w;
        for(int j=0; j<8; j++) {
            int nx=x+dx[j], ny=y+dy[j];
            if(in(nx,ny)) ret.push_back(index(nx,ny));
        }
        return ret;
    }

    bool is_even(int x, int y) { return (x+y)%2==0; }

    vector<int> operator()(int i) { return around4(i); }
    vector<pair<int,int>> operator()(int x, int y) { return around4(x,y); }
};