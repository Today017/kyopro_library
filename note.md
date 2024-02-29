[top](./README.md)

# Note

## 使い方

1. このディレクトリを作業フォルダ内に clone する。
2. [`exp.py`](./exp.py) を作業フォルダ内に移す。
3. `cpp` ファイルを作成する。ライブラリを利用する際は、例えば次のように記述する。

```cpp
#include "./kyopro_library/template.cpp"
#include "./kyopro_library/graph/dsu.cpp"
#include "./kyopro_library/mod/modint.cpp"

int main() {
    // code
    int N;
    cin >> N;
    disjoint_set_union dsu(N);
}
```

4. 次のコマンドを実行する。すると、ライブラリが展開されたものが `combind.cpp` として生成される。

`python3 exp.py a.cpp`