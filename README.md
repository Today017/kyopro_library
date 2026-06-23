[ライブラリのドキュメント](https://today017.github.io/kyopro_library/html/index.html)

## 環境構築
1. Docker, Git, make のインストール
2. [build](https://github.com/Today017/kyopro_library/blob/main/kyopro_tools/scripts/build) （AHCの場合は [build_AHC](https://github.com/Today017/kyopro_library/blob/main/kyopro_tools/scripts/build_AHC)）をコピペ、実行
3. `make build` でDockerイメージをビルドする（初回、および Dockerfile 変更時のみ）
4. `make nvim` でコンテナを起動して neovim を開く（`make bash` で bash を開く）

### make のターゲット
- `make build` Dockerイメージをビルド（Dockerfile変更時のみ）
- `make nvim` コンテナで neovim を開く（無ければ自動作成）
- `make bash` コンテナで bash を開く（無ければ自動作成）
- `make stop` コンテナを停止（次回 `make nvim` で即再開）
- `make down` コンテナを停止+削除（コード/プラグインは保持）
- `make rebuild` Dockerfile変更を反映（down→build→再作成）
- `make clean` イメージも削除
- `make purge` nvimプラグインのvolumeまで完全削除

## スクリプト
- `./file <file>` テンプレートから `<file>.cpp` を生成する。
- `./cmp <file> [t]` `<file>` をコンパイルする。`t` を指定すると、デバッグモード（`-DDEBUG`）が有効になる。
- `./copy <file> [t] [o]` `<file>` にincludeしたライブラリを展開し、`./combined.cpp` に保存してクリップボードにコピーする。`t` を指定するとAtCoder Libraryも展開し、`o` を指定すると `#ifdef TODAY_KYOPRO` を使わず素朴に展開する。
- `./test <solve> <generate> <naive> [testcount]` ランダムテスト用スクリプト。`<generate>` で生成した入力を `<solve>` と `<naive>` に与え、出力を比較する。テストケースは `./random_test/` に保存される。
- `./rand <solve> <naive> <generate>` `./test` の簡易版。一時ディレクトリを使い、出力が不一致になるまでループする。
- `./check <solve> <generate>` `<generate>` の入力で `<solve>` を実行し、異常終了（RE）するまでループする。RE の発見に使う。
- `./contest` カレントディレクトリで作成した解答ファイルや生成物を削除する。スクリプト・ライブラリ・`kp` 関連・`code`/`z` で始まるファイルは残す。コンテスト前に実行する。
- `kp` 自作 online-judge-tools（AtCoder / Codeforces 対応）。`kp -d <URL>` でサンプルを `./samples/` に取得し、`kp <問題番号> [t]` でコンパイル・サンプル実行・出力比較を行う。`KP_FIREFOX_PROFILE` などの環境変数で挙動を調整できる。

## 使い方
1. `./file a` で `a.cpp` を生成する
    ```cpp
    #include<kyopro_library/template.hpp>
    #include<kyopro_library/graph/dsu.hpp> // 使うライブラリをincludeする
    //------>8------------------------------------------->8------

    void run() {
        // ここに解答を実装する（main は template.hpp が提供する）
    }

    void prep() {}
    ```
2. `./cmp a` でコンパイルする
3. `./a.out` で実行する（`kp a` でサンプルテストもできる）
4. `./copy a` で提出用に展開する
