#include "../../kyopro_library/template.hpp"

struct {
    int h, w;
    ll sign;
    ll dat[12][12][1010][1010];
    ll log2[5050];
} sparse_table;

void sparse_table_init(const vector<vector<ll>>& a, bool is_min = true) {
    if (!is_min) {
        sparse_table.sign = -1;
    }
    sparse_table.h = a.size();
    sparse_table.w = a[0].size();
    for (int i = 0; i < sparse_table.h; i++) {
        for (int j = 0; j < sparse_table.w; j++) {
            sparse_table.dat[0][0][i][j] = sparse_table.sign * a[i][j];
        }
    }
    for (int i = 2; i <= max(sparse_table.h, sparse_table.w); i++) {
        sparse_table.log2[i] = sparse_table.log2[i / 2] + 1;
    }
    for (int k = 1; (1 << k) <= sparse_table.h; k++) {
        for (int i = 0; i + (1 << k) <= sparse_table.h; i++) {
            for (int j = 0; j < sparse_table.w; j++) {
                sparse_table.dat[k][0][i][j] = min(sparse_table.dat[k - 1][0][i][j], sparse_table.dat[k - 1][0][i + (1 << (k - 1))][j]);
            }
        }
    }
    for (int k = 0; (1 << k) <= sparse_table.h; k++) {
        for (int l = 1; (1 << l) <= sparse_table.w; l++) {
            for (int i = 0; i + (1 << k) <= sparse_table.h; i++) {
                for (int j = 0; j + (1 << l) <= sparse_table.w; j++) {
                    sparse_table.dat[k][l][i][j] = min(sparse_table.dat[k][l - 1][i][j], sparse_table.dat[k][l - 1][i][j + (1 << (l - 1))]);
                }
            }
        }
    }
}

ll sparse_table_query(int x1, int x2, int y1, int y2) {
    int k = sparse_table.log2[x2 - x1];
    int l = sparse_table.log2[y2 - y1];
    return min({sparse_table.dat[k][l][x1][y1], sparse_table.dat[k][l][x2 - (1 << k)][y1], sparse_table.dat[k][l][x1][y2 - (1 << l)], sparse_table.dat[k][l][x2 - (1 << k)][y2 - (1 << l)]}) * sparse_table.sign;
}