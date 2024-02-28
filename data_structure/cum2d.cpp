#include "../../kyopro_library/template.cpp"

template<typename T>
struct cumsum2D {
    template<typename U>
    cumsum2D(vector<vector<U>> &a) {
        n = a.size();
        m = a.front().size();
        rui = vector<vector<T>>(n + 1, vector<T>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                rui[i + 1][j + 1] = rui[i][j + 1] + rui[i + 1][j] - rui[i][j] + a[i][j];
            }
        }
    }
    T sum(int l, int r, int u, int d) {
        return rui[r][d] - rui[l][d] - rui[r][u] + rui[l][u];
    }

private:
    int n, m;
    vector<vector<T>> rui;
};
