## Today03
- [AtCoder](https://atcoder.jp/users/Today03)
- [Codeforces](https://codeforces.com/profile/Today03)
- [yukicoder](https://yukicoder.me/users/15224)

[ライブラリのドキュメント](https://today017.github.io/kyopro_library/html/index.html)

## 環境構築
1. Docker, Git, make のインストール
3. [build](https://github.com/Today017/kyopro_library/blob/main/kyopro_tools/scripts/build) をコピペ、実行
4. `make build` でDockerイメージをビルドする（初回のみ）
5. `make run` でコンテナを起動して入る

## スクリプト
- `./cmp <file>` `<file>` をコンパイルする。
- `./copy <file>` `<file>` にincludeしたライブラリを展開し、`./combinded.cpp` に保存する。
- `./test <solve> <generate> <naive>` ランダムテスト用スクリプト。`<solve>` を実行し、`<generate>` で生成した入力を与え、`<naive>` で生成した出力と比較する。
- `./contest` カレントディレクトリで作成したファイルを削除する。スクリプトやライブラリは削除しない。コンテスト前に実行する。

## 使い方
1. `vim a.cpp`
    ```cpp
    #include<kyopro_library/template.hpp>
    #include<kyopro_library/graph/dsu.hpp> // 使うライブラリをincludeする

    int main(){
        // ここにコードを実装する
    }
    ```
2. `./cmp a`
3. `./a.out`
4. `./copy a`

## データ構造に載せる代数構造の定義の仕方

### 例) モノイド
```cpp
struct Monoid {
    using Type = hoge;
    static Type id() { return hoge; }
    static Type op(const Type& l, const Type& r) { return hoge; }
};
```

### 各構造の要件
- モノイド
  - `Type id()`
  - `Type op(const Type& l, const Type& r)`
- 半群
  - `Type op(const Type& l, const Type& r)`
- 群
  - `Type inv(const Type& x)`
  - `Type op(const Type& l, const Type& r)`
  - `Type id()`
- 作用素
  - `Type id()`
  - `Type op(const Type& l, const Type& r)`