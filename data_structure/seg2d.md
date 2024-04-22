[top](../README.md)

# [Segment Tree 2D](./seg2d.hpp)

`segment_tree_2D<T>(int h, int w, F f, T e)`
- サイズ $h\times w$ ,演算 $f$, 単位元 $e$ の Segment Tree を構築する。
- 集合 $T$, 演算 $f$, 単位元 $e$ が単位半群を為すことを要求する。
- $O(hw)$

`void set(int x, int y, T v)`
- 位置 $(x, y)$ の要素を $v$ に変える。
- $O(\log{h}\log{w})$

`T query(int l, int r, int u, int d)`
- 矩形領域 $[l, r) \times [u, d)$ に対しての演算結果を返す。
- $O(\log{h}\log{w})$

---

```cpp
template <typename T>
struct segment_tree_2D {
    using F = function<T(T, T)>;
    segment_tree_2D(int h, int w, F f, T fe) {
        this->f = f;
        this->fe = fe;
        this->h = h;
        this->w = w;
        dat = vector<vector<T>>(this->h * 2, vector<T>(this->w * 2, fe));
    }
    void set(int x, int y, T v) {
        x += h;
        y += w;
        dat[x][y] = v;
        for (int i = x >> 1; i > 0; i >>= 1) {
            dat[i][y] = f(dat[i << 1][y], dat[i << 1 | 1][y]);
        }
        while (x > 0) {
            for (int j = y >> 1; j > 0; j >>= 1) {
                dat[x][j] = f(dat[x][j << 1], dat[x][j << 1 | 1]);
            }
            x >>= 1;
        }
    }
    T query(int x1, int x2, int y1, int y2) {
        T ret = fe;
        x1 += h;
        x2 += h;
        y1 += w;
        y2 += w;
        while (x1 < x2) {
            if (x1 & 1) {
                ret = f(ret, query_sub(x1, y1, y2));
                x1++;
            }
            if (x2 & 1) {
                x2--;
                ret = f(ret, query_sub(x2, y1, y2));
            }
            x1 >>= 1;
            x2 >>= 1;
        }
        return ret;
    }

private:
    int h, w;
    vector<vector<T>> dat;
    F f;
    T fe;
    T query_sub(int x, int y1, int y2) {
        T ret = fe;
        while (y1 < y2) {
            if (y1 & 1) {
                ret = f(ret, dat[x][y1]);
                y1++;
            }
            if (y2 & 1) {
                y2--;
                ret = f(ret, dat[x][y2]);
            }
            y1 >>= 1;
            y2 >>= 1;
        }
        return ret;
    }
};
```