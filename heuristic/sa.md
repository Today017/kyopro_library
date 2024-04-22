[top](../README.md)

# [Simulated Annealing](./sa.hpp)

`simulated_annealing<Data, MAX>(double start_temp, double end_temp, ll time_limit)`
- Data 型に対して、開始温度 `start_temp`, 終了温度 `end_temp`, 実行時間 `time_limit` ms の焼きなまし法を適用する。

`Data run()`
- 焼きなまし法を実行し、最高スコアを出した状態の Data を返す。

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

---

```cpp
template<typename Data, bool MAX = true>
struct simulated_annealing {
    double start_temp, end_temp, temp;
    timer t;
    Data best, now;
    inline const double get_temp() {
        return start_temp + (end_temp - start_temp) * (t.get() / time_limit);
    }
    inline const double get_prob(double dE) {
        return exp(dE / temp);
    }
    simulated_annealing(double start_temp = 1e5, double end_temp = 1e2, ll time_limit) {
        this->start_temp = start_temp;
        this->end_temp = end_temp;
        t = timer(time_limit);
        temp = start_temp;
        now.init();
    }
    Data run() {
        while(t.check()) {
            double next_score = now.get_next_score();
            double dE = next_score - now.get_score();
            if (!MAX) {
                dE *= -1;
            }
            double temp = get_temp();
            double prob = get_prob(dE);
            if(1.0 * random_generator::random_int(1000000) / 1000000 < prob) {
                now.modify();
                if(now.get_score() > best.get_score()) {
                    best.record(now);
                }
            }
        }
        return best;
    }
};
```