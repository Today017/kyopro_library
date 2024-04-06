[top](../README.md)

# [Simulated Annealing](./sa.cpp)

`simulated_annealing<Data, MAX>(double start_temp, double end_temp, double time_limit)`
- Data 型に対して、開始温度 `start_temp`, 終了温度 `end_temp`, 実行時間 `time_limit` ms の焼きなまし法を適用する。

`Data run()`
- 焼きなまし法を実行し、最高スコアを出した状態の Data を返す。

---

```cpp
#include "../../kyopro_library/template.cpp"
#include "../../kyopro_library/others/timer.cpp"
#include "../../kyopro_library/others/random.cpp"

template<typename Data, bool MAX = true>
struct simulated_annealing {
    double start_temp, end_temp, temp;
    double time_limit;
    timer t;
    Data best, now;
    double get_temp() {
        return start_temp + (end_temp - start_temp) * (t.get() / time_limit);
    }
    double get_prob(double dE) {
        return exp(dE / temp);
    }
    simulated_annealing(double start_temp, double end_temp, double time_limit) {
        this->start_temp = start_temp;
        this->end_temp = end_temp;
        this->time_limit = time_limit;
        t = timer(time_limit);
        temp = start_temp;
    }
    Data run() {
        while(t.check()) {
            Data next = now.get_next();
            double dE = next.get_score() - now.get_score();
            if (!MAX) {
                dE *= -1;
            }
            double temp = get_temp();
            double prob = get_prob(dE);
            if(1.0 * random_generator::randint(1000000) / 1000000 < prob) {
                now = next;
                if(now.get_score() > best.get_score()) {
                    best = now;
                }
            }
        }
        return best;
    }
};

```