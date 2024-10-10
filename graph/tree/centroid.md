[top](../../README.md)

# [Centroid](./centroid.hpp)

`vector<int> getCentroid(const vector<vector<int>> &g, int root, vector<bool> seen, vector<int> sz)`
- 木 $g$ の重心を返す。
- `root` は根、`seen` は重心分解における訪問フラグ、`sz` は部分木のサイズとする。
- $O(V)$

## 重心分解の雛形
```cpp
vector<int> sz(N);
vector<bool> seen(N);

auto centroid_decomposition = [&](auto self, int now) -> void {
    int centroid = getCentroid(g, now, seen, sz);
    seen[centroid] = true;

    // ここに処理を書く

    for (int nxt : g[centroid]) {
        if (seen[nxt]) continue;
        self(self, nxt);
    }
};
centroid_decomposition(centroid_decomposition, 0);
```