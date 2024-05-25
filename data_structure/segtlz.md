[top](../README.md)

# [Segment Tree Lazy](./segtlz.hpp)

`segment_tree_lezy<T, U>(int n, F f, G g, H h, T et, U eu)`
- 遅延評価 Segment Tree を構築する。
- 以下の条件を要求する。
    - 集合 $T$, 演算 $f$, 単位元 $et$ が単位半群を成す。
    - 集合 $U$, 演算 $h$, 単位元 $eu$ が単位半群を為す。
    - 演算 $g:U\times T \rightarrow T$ が $t, t_1, t_2 \in T, u, u_1, u_2 \in U$ について以下を満たす。
        - $g(m_2, g(m_1, t)) = g(h(m_2, m_1), t)$
        - $g(m, f(t_1, t_2)) = f(g(m, t_1), g(m, t_2))$

`void build(vector<T> a)`
- 配列 $a$ から 遅延評価 Segment Tree を構築する。
- $O(n)$

`void set(int i, T x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`T query(int l, int r)`
- 区間 $[l, r)$ に対しての演算結果を返す。
- $O(\log{n})$

`void apply(int l, int r, U x)`
- 区間 $[l, r)$ に対して $x$ を作用させる。
- $O(\log{n})$

`T operator[int i]`
- 位置 $i$ の要素。
- $O(\log{n})$
- 遅延伝播を検査する必要があるため。

### 区間加算 / 区間 min
```cpp
template <typename T, typename U>
segment_tree_lazy<T, U> range_add_range_min(int n) {
    const T et = numeric_limits<T>::max();
    const U eu = 0;
    auto f = [](T a, T b) {
        return min(a, b);
    };
    auto g = [](U f, T x) {
        return f + x;
    };
    auto h = [](U f, U g) {
        return f + g;
    };
    return segment_tree_lazy<T, U>(n, f, g, h, et, eu);
}
```

### 区間加算 / 区間 max
```cpp
template <typename T, typename U>
segment_tree_lazy<T, U> range_add_range_max(int n) {
    const T et = numeric_limits<T>::min();
    const U eu = 0;
    auto f = [](T a, T b) {
        return max(a, b);
    };
    auto g = [](U f, T x) {
        return f + x;
    };
    auto h = [](U f, U g) {
        return f + g;
    };
    return segment_tree_lazy<T, U>(n, f, g, h, et, eu);
}
```

### 区間加算 / 区間和
```cpp
template <typename T, typename U>
segment_tree_lazy<pair<T, int>, U> range_add_range_sum(int n) {
    using T2 = pair<T, int>;
    const T2 et = make_pair(T(0), 0);
    const U eu = 0;
    auto f = [](T2 a, T2 b) {
        return make_pair(a.first + b.first, a.second + b.second);
    };
    auto g = [](U f, T2 x) {
        return make_pair(x.first + (T)f * x.second, x.second);
    };
    auto h = [](U f, U g) {
        return f + g;
    };
    return segment_tree_lazy<T2, U>(n, f, g, h, et, eu);
}
```

### 区間更新 / 区間 min
```cpp
template <typename T>
segment_tree_lazy<T, T> range_update_range_min(int n, T eu = numeric_limits<T>::max()) {
    const T et = numeric_limits<T>::max();
    auto f = [](T a, T b) {
        return min(a, b);
    };
    auto g = [eu](T f, T x) {
        if (f == eu) {
            return x;
        }
        return f;
    };
    return segment_tree_lazy<T, T>(n, f, g, g, et, eu);
}
```

### 区間更新 / 区間 max
```cpp
template <typename T>
segment_tree_lazy<T, T> range_update_range_max(int n, T eu = numeric_limits<T>::max()) {
    const T et = numeric_limits<T>::min();
    auto f = [](T a, T b) {
        return max(a, b);
    };
    auto g = [eu](T f, T x) {
        if (f == eu) {
            return x;
        }
        return f;
    };
    return segment_tree_lazy<T, T>(n, f, g, g, et, eu);
}
```

### 区間更新 / 区間和
```cpp
template <typename T>
segment_tree_lazy<pair<T, int>, T> range_update_range_sum(int n, T eu = numeric_limits<T>::max()) {
    using T2 = pair<T, int>;
    const T2 et = make_pair(T(0), 0);
    auto f = [](T2 a, T2 b) {
        return make_pair(a.first + b.first, a.second + b.second);
    };
    auto g = [eu](T f, T2 x) {
        if (f == eu) {
            return x;
        }
        return make_pair(f * x.second, x.second);
    };
    auto h = [eu](T f, T g) {
        if (f == eu) {
            return g;
        }
        return f;
    };
    return segment_tree_lazy<T, T>(n, f, g, h, et, eu);
}
```