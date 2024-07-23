[top](../README.md)

# [Random Generator](./random.hpp)

`namespace RandomGenerator`
- ランダムテストケース生成用ツール。

`void init()`
- シード値を設定する。

`T randomInt(T x)`
- $[0, x)$ の範囲でランダムな整数を生成する。

`T randomInt(T l, T r)`
- $[l, r)$ の範囲でランダムな整数を生成する。

`T getElement(vector<T> a)`
- $a$ の中でランダムな要素を取得し、削除する。

`vector<T> randomArray(int n, int lo, int hi, bool no_dup)`
- 長さ $n$, 範囲 $[l, r)$ のランダムな数列を生成する。
- `no_dup` を `true` とすると、重複のない数列となる。

`string randomAlphabet(int n, bool lower = true)`
- 長さ $n$ のアルファベットからなるランダムな文字列を生成する。
- `lower` を `false` とすると uppercase のみからなる文字列となる。

`string randomString(int n, string s)`
- 長さ $n$, 文字列 $s$ の要素からなるランダムな文字列を生成する。

`vector<vector<T>> randomArray2D(int h, int w, T lo, T hi)`
- 縦、横の長さ $h$, $w$, 範囲 $[lo, hi)$ のランダムな 2 次元の数列を生成する。

`vector<string> randomAlphabet2D(int h, int w, bool lower)`
- 縦、横の長さ $h$, $w$, のランダムな文字列列を生成する。
- `lower` を `false` とすると uppercase のみからなる文字列となる。

`vector<pair<int, int>> randomTree(int n)`
- 頂点数 $n$ の木を生成する。`1-indexed` 。

`vector<pair<int, int>> randomBinaryTree(int n)`
- 頂点数 $n$ の完全二分木を生成する。`1-indexed` 。

`vector<pair<int, int>> randomUndirectedGraph(int n, int m, bool connected)`
- 頂点数 $n$, 辺数 $m$ の無向グラフを生成する。`connected` を `false` とすると連結とは限らないグラフを生成する。