[top](../README.md)

# [Segment Tree](./segt.cpp)

`segment_tree<T>(int n, F f, T e)`
- サイズ $n$ ,演算 $f$, 単位元 $e$ の Segment Tree を構築する。
- 集合 $T$, 演算 $f$, 単位元 $e$ が単位半群を為すことを要求する。
- $O(n)$

`void build(vector<T> a)`
- 配列 $a$ から Segment Tree を構築する。
- $O(n)$

`void set(int i, T x)`
- 位置 $i$ の要素を $x$ に変える。
- $O(\log{n})$

`T query(int l, int r)`
- 区間 $[l, r)$ に対しての演算結果を返す。
- $O(\log{n})$

`T operator[int i]`
- 位置 $i$ の要素。
- $O(1)$

### 区間 min
```cpp
template <typename T>
segment_tree<T> range_min_query(int n, T e = numeric_limits<T>::max()) {
    auto f = [](T a, T b) {
        return min(a, b);
    };
    return segment_tree<T>(n, f, e);
}
```

### 区間 max
```cpp
template <typename T>
segment_tree<T> range_max_query(int n, T e = numeric_limits<T>::min()) {
    auto f = [](T a, T b) {
        return max(a, b);
    };
    return segment_tree<T>(n, f, e);
}
```

### 区間和
```cpp
template <typename T>
segment_tree<T> range_sum_query(int n, T e = 0) {
    auto f = [](T a, T b) {
        return a + b;
    };
    return segment_tree<T>(n, f, e);
}
```

---

```cpp
template <typename T>
struct segment_tree {
    using F = function<T(T, T)>;
    segment_tree(int n, F f, T e) {
        this->n = 1;
        while (this->n < n) {
            this->n *= 2;
        }
        this->size = n;
        this->f = f;
        this->e = e;
        dat = vector<T>(this->n * 2 - 1, e);
    }
    void build(const vector<T> &a) {
        for (int i = 0; i < (int)a.size(); i++) {
            dat[i + n - 1] = a[i];
        }
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    void set(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;
            dat[i] = f(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }
    T query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
    T operator[](int i) {
        return dat[n - 1 + i];
    }
    int size;

private:
    int n;
    vector<T> dat;
    F f;
    T e;
    T query(int left, int right, int i, int l, int r) {
        if (r <= left || right <= l) {
            return e;
        } else if (left <= l && r <= right) {
            return dat[i];
        } else {
            int mid = (l + r) / 2;
            return f(query(left, right, i * 2 + 1, l, mid), query(left, right, i * 2 + 2, mid, r));
        }
    }
};
```