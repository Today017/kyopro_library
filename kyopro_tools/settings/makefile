# Makefile

IMAGE_NAME     := kyopro-env
CONTAINER_NAME := kyopro-container
WORKDIR        := $(shell pwd)

# デフォルトターゲット（ヘルプ表示）
.DEFAULT_GOAL := help

# 使い方表示
help:
	@echo "usage:"
	@echo "  make build   - Dockerイメージをビルド（Dockerfile変更時のみ）"
	@echo "  make nvim    - コンテナで neovim を開く（無ければ自動作成）"
	@echo "  make bash    - コンテナで bash を開く（無ければ自動作成）"
	@echo "  make stop    - コンテナを停止（次回 make nvim で即再開）"
	@echo "  make down    - コンテナを停止+削除（コード/プラグインは保持）"
	@echo "  make rebuild - Dockerfile変更を反映（down→build→再作成）"
	@echo "  make clean   - イメージも削除"
	@echo "  make purge   - nvimプラグインのvolumeまで完全削除"

# Dockerイメージのビルド
build:
	docker build -t $(IMAGE_NAME) .

# コンテナを起動状態にする
#   停止中→start / 存在しない→run で作成 / 起動中→何もしない
up:
	@docker start $(CONTAINER_NAME) >/dev/null 2>&1 || \
	docker run -dit --name $(CONTAINER_NAME) \
		-v $(WORKDIR):/workspace \
		-v $(HOME)/.config/nvim:/root/.config/nvim \
		-v $(HOME)/.clang-format:/.clang-format:ro \
		-v kyopro-nvim-data:/root/.local/share/nvim \
		-v kyopro-nvim-state:/root/.local/state/nvim \
		$(IMAGE_NAME)

# コンテナで neovim を開く
nvim: up
	docker exec -it $(CONTAINER_NAME) nvim

# コンテナで bash を開く
bash: up
	docker exec -it $(CONTAINER_NAME) bash

# 毎回の後処理：止めるだけ（コンテナは残る＝次回が速い）
stop:
	-docker stop $(CONTAINER_NAME)

# 不要時の後処理：コンテナを削除（/workspaceのコードとvolumeは無事）
down:
	-docker stop $(CONTAINER_NAME)
	-docker rm   $(CONTAINER_NAME)

# Dockerfileを変更したときの反映
rebuild: down build up

# イメージも削除
clean: down
	-docker rmi $(IMAGE_NAME)

# nvimプラグインのvolumeまで完全削除
purge: clean
	-docker volume rm kyopro-nvim-data kyopro-nvim-state
