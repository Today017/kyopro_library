[top](../README.md)

# [Timer](./timer.hpp)

`Timer(ll time_limit_msec)`
- `time_limit_msec` msec を制限時間とした Timer を定義し、時間の計測を開始する。

`ll get()`
- 今が計測開始から何 msec 後かを返す。

`bool check()`
- 今が制限時間内であるか否かを返す。