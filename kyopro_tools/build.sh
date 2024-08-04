#!/bin/bash

# 環境側でやること
# 1. GCCのインストール
#   - C++20が使える
#   - #include <bits/stdc++.h> が使える
# 2. Python3のインストール
# 3. ~/.vimrc を設定する
# 4. ~/.bashrc / ~/.zshrc で pbcopy をコピー用のエイリアスとして設定する

# chmod 755 build.sh

git clone https://github.com/Today017/kyopro_library.git

touch .clang-format
cp kyopro_library/kyopro_tools/.clang-format .clang-format

touch makefile
cp kyopro_library/kyopro_tools/makefile makefile

touch test.sh
cp kyopro_library/kyopro_tools/test.sh test.sh
chmod 755 test.sh

touch exp.py
cp kyopro_library/kyopro_tools/exp.py exp.py

mkdir test

