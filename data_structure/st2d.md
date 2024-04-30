[top](../README.md)

# [Sparse Table 2D](./st2d.hpp)

`void sparse_table_init(vector<vector<ll>> a, bool is_min=true)`
- 2 次元配列 `a` に対して 2 次元の Sparse Table を構築する。
- $O(HW\log{H}\log{W})$

`ll sparse_table_query(int l, int r, int u, int d)`
- 矩形領域 $[l, r) \times [u, d)$ における最小値を返す。
- $O(1)$

---

```cpp
struct {
    int h, w;
    ll sign;
    ll dat[12][12][1010][1010];
    ll log_table[5050];
} sparse_table_2D;

void sparse_table_2D_init(const vector<vector<ll>>& a, bool is_min = true) {
    if (!is_min) {
        sparse_table_2D.sign = -1;
    }
    sparse_table_2D.h = a.size();
    sparse_table_2D.w = a[0].size();
    for (int i = 0; i < sparse_table_2D.h; i++) {
        for (int j = 0; j < sparse_table_2D.w; j++) {
            sparse_table_2D.dat[0][0][i][j] = sparse_table_2D.sign * a[i][j];
        }
    }
    for (int i = 2; i <= max(sparse_table_2D.h, sparse_table_2D.w); i++) {
        sparse_table_2D.log_table[i] = sparse_table_2D.log_table[i / 2] + 1;
    }
    for (int k = 1; (1 << k) <= sparse_table_2D.h; k++) {
        for (int i = 0; i + (1 << k) <= sparse_table_2D.h; i++) {
            for (int j = 0; j < sparse_table_2D.w; j++) {
                sparse_table_2D.dat[k][0][i][j] = min(sparse_table_2D.dat[k - 1][0][i][j], sparse_table_2D.dat[k - 1][0][i + (1 << (k - 1))][j]);
            }
        }
    }
    for (int k = 0; (1 << k) <= sparse_table_2D.h; k++) {
        for (int l = 1; (1 << l) <= sparse_table_2D.w; l++) {
            for (int i = 0; i + (1 << k) <= sparse_table_2D.h; i++) {
                for (int j = 0; j + (1 << l) <= sparse_table_2D.w; j++) {
                    sparse_table_2D.dat[k][l][i][j] = min(sparse_table_2D.dat[k][l - 1][i][j], sparse_table_2D.dat[k][l - 1][i][j + (1 << (l - 1))]);
                }
            }
        }
    }
}

ll sparse_table_2D_query(int x1, int x2, int y1, int y2) {
    int k = sparse_table_2D.log_table[x2 - x1];
    int l = sparse_table_2D.log_table[y2 - y1];
    return min({sparse_table_2D.dat[k][l][x1][y1], sparse_table_2D.dat[k][l][x2 - (1 << k)][y1], sparse_table_2D.dat[k][l][x1][y2 - (1 << l)], sparse_table_2D.dat[k][l][x2 - (1 << k)][y2 - (1 << l)]}) * sparse_table_2D.sign;
}
```