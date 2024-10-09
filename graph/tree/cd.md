[top](../../README.md)

# [Centroid Decomposition](./cd.hpp)

`CentroidDecomposition(vector<vector<int>> g, int root = 0)`
- 木 $g$ に対し、 $root$ を根として重心分解を行う。

`pair<int, vector<vector<int>>> decompose()`
- 重心分解後の木を返す。
- $($ 重心, 分解木（ある部分木の重心があり、その子に重心の部分木の重心が入っているような木） $)$ を返す。

`vector<int> get_parent()`
- 重心分解後の木の親を返す。

---

```cpp
#include "../../../kyopro_library/template.hpp"

struct CentroidDecomposition {
    CentroidDecomposition(const vector<vector<int>> &g, int root = 0) {
        n = g.size();
        graph = g;
        subtree_size = vector<int>(n);
        parent = vector<int>(n, -1);
        seen = vector<bool>(n, false);
        build(root, -1);
    }
    pair<int, vector<vector<int>>> decompose() {
        vector<vector<int>> new_graph(n);
        int root = -1;
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                new_graph[i].push_back(parent[i]);
                new_graph[parent[i]].push_back(i);
            } else {
                root = i;
            }
        }
        return {root, new_graph};
    }
    vector<int> get_parent() {
        return parent;
    }

private:
    int n;
    vector<vector<int>> graph;
    vector<int> subtree_size, parent;
    vector<bool> seen;
    void build(int root, int pre) {
        int total = compute_subtree_size(root, pre);
        int centroid = find_centroid(root, pre, total);
        parent[centroid] = pre;
        seen[centroid] = true;
        for (int child : graph[centroid]) {
            if (!seen[child]) {
                build(child, centroid);
            }
        }
    }
    int compute_subtree_size(int now, int pre) {
        subtree_size[now] = 1;
        for (int nxt : graph[now]) {
            if (nxt == pre || seen[nxt]) continue;
            subtree_size[now] += compute_subtree_size(nxt, now);
        }
        return subtree_size[now];
    }
    int find_centroid(int now, int pre, int total) {
        int heaviest_child = -1;
        for (int nxt : graph[now]) {
            if (nxt == pre || seen[nxt]) continue;
            if (heaviest_child == -1 || subtree_size[nxt] > subtree_size[heaviest_child]) {
                heaviest_child = nxt;
            }
        }
        if (heaviest_child != -1 && subtree_size[heaviest_child] * 2 > total) {
            return find_centroid(heaviest_child, now, total);
        }
        return now;
    }
};
```