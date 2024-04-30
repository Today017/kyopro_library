[top](../README.md)

# [Cumulative Sum 2D](./cum2d.hpp)

`cumulative_sum_2D<U, T>(vector<vector<U>> a)`
- 行列 $a$ に対する2次元累積和を構築する。
- $O(hw)$

`T sum(int l, int r, int u, int d)`
- 矩形領域 $[l, r) \times [u, d)$ における累積和。
- $O(1)$

---

```cpp
template<typename T>
struct cumulative_sum_2D {
    template<typename U>
    cumulative_sum_2D(vector<vector<U>> &a) {
        n = a.size();
        m = a.front().size();
        dat = vector<vector<T>>(n + 1, vector<T>(m + 1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dat[i + 1][j + 1] = dat[i][j + 1] + dat[i + 1][j] - dat[i][j] + a[i][j];
            }
        }
    }
    T sum(int l, int r, int u, int d) {
        return dat[r][d] - dat[l][d] - dat[r][u] + dat[l][u];
    }

private:
    int n, m;
    vector<vector<T>> dat;
};


```