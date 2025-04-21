FROM ubuntu:22.04

# 基本ツールのインストール
RUN apt-get update && apt-get install -y \
    build-essential \
    clang \
    g++ \
    cmake \
    python3 \
    python3-pip \
    git \
    curl \
    vim \
    sudo \
    && apt-get clean

# 任意: atcoder-toolsのインストール（Pythonが使えるなら）
RUN pip3 install online-judge-tools

# 作業ディレクトリの設定
WORKDIR /workspace

# デフォルトでシェルを起動
CMD [ "bash" ]

