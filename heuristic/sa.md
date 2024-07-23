[top](../README.md)


# 焼きなまし法のテンプレート

```cpp
const double START_TEMP = 1e4;
const double END_TEMP = 1e-4;
const ll TIME_LIMIT = 5000;

Random rnd;

void solve() {
    Timer timer(TIME_LIMIT);

    // 初期状態
    State now = initialState();
    State best = now;


    while (timer.check()) {
        // 近傍
        double next_score = now.get_next_score();
        double diff = next_score - now.get_score();
        double temp = START_TEMP + (END_TEMP - START_TEMP) * timer.get_time() / TIME_LIMIT;
        double prob = exp(diff / temp);

        if (rnd.prob() < prob) {
            // 遷移
            now.modify();
            if (now.get_score() > best.get_score()) {
                // 記録
                best = now;
            }
        }
    }
}
```