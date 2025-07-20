#include"../../kyopro_library/template.hpp"

template<typename Monoid>
struct SegmentTree2D {
    using Type=Monoid::Type;

    SegmentTree2D()=default;

    /// @brief サイズ h * w の２次元セグメント木を構築する
    SegmentTree2D(int h, int w) {
        this->h=h; this->w=w;
        dat=vector<vector<Type>>(this->h*2,vector<Type>(this->w*2,Monoid::id()));
    }

    /// @brief 位置 (x, y) の要素を v に更新する
    /// @note O(log(h) log(w))
    void set(int x, int y, Type v) {
        x+=h; y+=w;
        dat[x][y]=v;
        for(int i=x>>1; i>0; i>>=1) dat[i][y]=Monoid::op(dat[i<<1][y],dat[i<<1|1][y]);
        while(x>0) {
            for(int j=y>>1; j>0; j>>=1) dat[x][j]=Monoid::op(dat[x][j<<1],dat[x][j<<1|1]);
            x>>=1;
        }
    }

    /// @brief 矩形領域 [l, r) × [u, d) のモノイド積を返す
    /// @note O(log(h) log(w))
    Type fold(int l, int r, int u, int d) {
        Type ret=Monoid::id();
        l+=h; r+=h; u+=w; d+=w;
        while(l<r) {
            if(l&1) ret=Monoid::op(ret,fold_sub(l++,u,d));
            if(r&1) ret=Monoid::op(ret,fold_sub(--r,u,d));
            l>>=1; r>>=1;
        }
        return ret;
    }

private:
    int h,w;
    vector<vector<Type>>dat;
    Type fold_sub(int x, int u, int d) {
        Type ret=Monoid::id();
        while(u<d) {
            if(u&1) ret=Monoid::op(ret,dat[x][u]),u++;
            if(d&1) d--,ret=Monoid::op(ret,dat[x][d]);
            u>>=1; d>>=1;
        }
        return ret;
    }
};