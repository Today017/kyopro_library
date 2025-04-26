FROM ubuntu:22.04

# 基本ツールのインストール
RUN apt-get update && apt-get install -y \
    g++ \
    python3 \
    python3-pip \
    git \
    curl \
    vim \
    sudo \
    && apt-get clean

# 作業ディレクトリの設定
WORKDIR /workspace

# デフォルトでシェルを起動
CMD [ "bash" ]

