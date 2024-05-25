[top](../README.md)

# [Climbing](./cl.hpp)

`climbing<Data, MAX>(double start_temp, double end_temp, ll time_limit)`
- Data 型に対して、開始温度 `start_temp`, 終了温度 `end_temp`, 実行時間 `time_limit` ms の山登り法を適用する。

`Data run()`
- 山登り法を実行し、最高スコアを出した状態の Data を返す。

### Data 型への要求
Data 型に対し、次の実装を要求する。

`ll init()`
- 状態を初期化する。

`double get_score()`
- 現在の状態のスコアを返す。

`double get_next_score()`
- 状態は変えないままで、近傍状態を探索し、その状態のスコアを返す。

`void modify()`
- `get_next_score()` にて探索した状態に遷移する。

`void record(Data other)`
- 他の状態とそのスコアを記録する。