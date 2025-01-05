[top](./README.md)

# Note

## 環境構築
- [Mac](./kyopro_tools/mac/build)
- [WSL](./kyopro_tools/linux/build)

### 環境側でやること
1. GCC のインストール
  - C++20 が使える
  - `#include <bits/stdc++.h>` が使える
2. Python3 のインストール
3. `~/.vimrc` を設定する

## データ構造に載せる代数構造

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