[top](./README.md)

# Note

## 使い方

1. このディレクトリを作業フォルダ内に clone する。
2. [`exp.py`](./exp.py) を作業フォルダ内に移す。
3. `hpp` ファイルを作成する。ライブラリを利用する際は、例えば次のように記述する。

```cpp
#include "./kyopro_library/template.hpp"
#include "./kyopro_library/graph/dsu.hpp"
#include "./kyopro_library/mod/modint.hpp"

int main() {
    // code
    int N;
    cin >> N;
    disjoint_set_union dsu(N);
}
```

4. 次のコマンドを実行する。すると、ライブラリが展開されたものが `combind.hpp` として生成される。

```bash
python3 exp.py a.hpp
```

## 注意点

1. 他の方のライブラリのコードを持ってきて命名規則やインターフェースを少し変えただけ、みたいなものが含まれます。一応ライセンスは確認し、出典も明記してありますが、問題がありましたらご連絡いただけると幸いです。
2. 全体にわたり、 `#include <bits/stdc++.h>` `using namespace std;` `using ll = long long;` を暗黙に使用しています。
3. このライブラリのコードは自由・無断に使用して構いません。ただし、コードの動作の正当性に関する責任は一切持たないので自己責任でお願いいたします。