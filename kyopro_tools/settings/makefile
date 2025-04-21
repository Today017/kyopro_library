# Makefile

IMAGE_NAME := kyopro-env
CONTAINER_NAME := kyopro-container
WORKDIR := $(shell pwd)

# デフォルトターゲット（ヘルプ表示）
.DEFAULT_GOAL := help

# 使い方表示
help:
	@echo "usage:"
	@echo "  make build     - Dockerイメージのビルド"
	@echo "  make run       - 1回限りの起動（終了時に削除）"
	@echo "  make start     - コンテナをバックグラウンドで起動"
	@echo "  make attach    - 起動中のコンテナに接続"
	@echo "  make stop      - コンテナを停止して削除"
	@echo "  make clean     - Dockerイメージを削除"
	@echo "  make help      - このメッセージを表示"

# Dockerイメージのビルド
build:
	docker build -t $(IMAGE_NAME) .

# 1回限りのコンテナ起動（終了時削除）
run:
	docker run -it --rm -v $(WORKDIR):/workspace $(IMAGE_NAME)

# バックグラウンド起動
start:
	docker run -dit --name $(CONTAINER_NAME) -v $(WORKDIR):/workspace $(IMAGE_NAME)

# 起動中のコンテナに接続
attach:
	docker exec -it $(CONTAINER_NAME) bash

# コンテナの停止と削除
stop:
	docker stop $(CONTAINER_NAME) && docker rm $(CONTAINER_NAME)

# イメージの削除
clean:
	docker rmi $(IMAGE_NAME)

