[top](../README.md)

# [Fenwick Tree](./fen.cpp)

`T add(int i, T x)`
- $0\le i\le n$
- $O(\log n)$

`T sum(int l, int r)`
- $0\le l<r\leq n$
- $O(\log n)$


### 区間加算1点取得を行う場合
```cpp
fenwick_tree<int> ft(N + 1);

// [l, r]に区間加算
ft.add(l, x);
ft.add(r + 1, x);

// i番目を取得
ft.sum(i + 1);
```

---

```cpp
template <typename T>
struct fenwick_tree {
    fenwick_tree(int n) {
        this->n = n;
        dat = vector<T>(n);
    }
    void add(int i, T x) {
        i++;
        while (i <= n) {
            dat[i - 1] += x;
            i += i & -i;
        }
    }
    T operator[](int i) {
        return sum(i, i + 1);
    }
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }
    friend ostream &operator<<(ostream &os, fenwick_tree A) {
        int n = A.n;
        os << "[ ";
        for (int i = 0; i < n; i++) {
            os << A[i];
            if (i != n - 1) os << ", ";
        }
        os << " ]";
        return os;
    }

private:
    int n;
    vector<T> dat;
    T sum(int r) {
        T ret = 0;
        while (r > 0) {
            ret += dat[r - 1];
            r -= r & -r;
        }
        return ret;
    }
};
```