[top](../README.md)

# [Cumulative Sum 2D](./cum2d.cpp)

`cumsum2D<U, T>(vector<vector<U>> a)`
- 行列 $a$ に対する2次元累積和を構築する。
- $O(hw)$

`T sum(int l, int r, int u, int d)`
- 矩形領域 $[l, r) \times [u, d)$ における累積和。
- $O(1)$

---

```cpp
template <typename U, typename T>
struct cumsum2D {
    cumsum2D(vector<vector<U>> &a) {
        n = a.size();
        m = a.front().size();
        acc = vector<vector<T>>(n + 1, vector<T>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                acc[i + 1][j + 1] = acc[i][j + 1] + acc[i + 1][j] - acc[i][j] + a[i][j];
            }
        }
    }
    T sum(int l, int r, int u, int d) {
        return acc[r][d] - acc[l][d] - acc[r][u] + acc[l][u];
    }

private:
    int n, m;
    vector<vector<T>> acc;
};

```