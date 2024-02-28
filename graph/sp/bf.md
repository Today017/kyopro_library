[top](../../README.md)

# [Bellman Ford](./bf.cpp)

`bool bellman_ford<T>(vector<tuple<int, int, T>> edge, int n, int start, vector<T> dst, T inf)`
- 辺集合 $edge$ に対して頂点 $start$ からの各頂点への最短距離を $dst$ に格納する。
- 負のサイクルが存在する場合 `true` を返す。
- $O(VE)$

---

```cpp
template <typename T>
bool bellman_ford(const vector<tuple<int, int, T>> &edge, int n, int start, vector<T> &dst) {
    dst = vector<T>(n, numeric_limits<T>::max());
    dst[start] = 0;
    int cnt = 0;
    while (cnt < n) {
        bool fin = true;
        for (auto [a, b, c] : edge) {
            if (dst[a] != inf && dst[a] + c < dst[b]) {
                dst[b] = dst[a] + c;
                fin = false;
            }
        }
        if (fin) {
            break;
        }
        cnt++;
    }
    return cnt == n;
}
```