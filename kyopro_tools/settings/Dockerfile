FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# 基本ツール + neovim 用ツールチェーン
#   build-essential: treesitter パーサや fzf-native のビルド用
#   ripgrep / fd-find: telescope の検索バックエンド
#   gnupg / ca-certificates: 下の LLVM apt リポジトリ追加に必要
#   （clangd は apt 版が古い(14)ため入れず、次のステップで LLVM 公式版を導入）
RUN apt-get update && apt-get install -y \
    g++ \
    python3 \
    python3-pip \
    git \
    curl \
    vim \
    sudo \
    build-essential \
    ripgrep \
    fd-find \
    unzip \
    gnupg \
    ca-certificates \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# 新しい clangd / clang-format を LLVM 公式 apt リポジトリから導入
#   Ubuntu 22.04 の apt 版は clangd 14（2022年）で C++20 サポートが不完全なため、
#   clangd 19 を入れて /usr/local/bin/clangd で使えるようにする。
#   clang-format も nvim の conform.nvim から呼ばれるので同じ 19 系を入れる。
RUN curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor -o /usr/share/keyrings/llvm.gpg \
    && echo "deb [signed-by=/usr/share/keyrings/llvm.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-19 main" \
       > /etc/apt/sources.list.d/llvm.list \
    && apt-get update && apt-get install -y clangd-19 clang-format-19 \
    && ln -sf /usr/bin/clangd-19 /usr/local/bin/clangd \
    && ln -sf /usr/bin/clang-format-19 /usr/local/bin/clang-format \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# 新しい neovim を公式リリースから導入（Ubuntu 22.04 の apt 版は古すぎる）
# Apple Silicon Mac の Docker は arm64 イメージになる点に対応
RUN ARCH="$(dpkg --print-architecture)" \
    && case "$ARCH" in \
         arm64) NVIM_ARCH="arm64" ;; \
         amd64) NVIM_ARCH="x86_64" ;; \
         *) echo "unsupported arch: $ARCH" && exit 1 ;; \
       esac \
    && curl -fsSL -o /tmp/nvim.tar.gz \
       "https://github.com/neovim/neovim/releases/download/stable/nvim-linux-${NVIM_ARCH}.tar.gz" \
    && tar -xzf /tmp/nvim.tar.gz -C /opt \
    && ln -s "/opt/nvim-linux-${NVIM_ARCH}/bin/nvim" /usr/local/bin/nvim \
    && rm /tmp/nvim.tar.gz

# 作業ディレクトリの設定
WORKDIR /workspace

# vimrcをコピー
COPY kyopro_library/kyopro_tools/settings/.vimrc /root/.vimrc

# デフォルトでシェルを起動
CMD [ "bash" ]

ENV LANG=C.UTF-8
ENV LANGUAGE=en_US:

# このコンテナ内であることを neovim 設定から判定するための目印
# （lsp.lua がこれを見て LSP サーバーを C++ 中心に絞る）
ENV KYOPRO_CONTAINER=1
