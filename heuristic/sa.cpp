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
    simulated_annealing(double start_temp, double end_temp, double time_limit, Data init) {
        this->start_temp = start_temp;
        this->end_temp = end_temp;
        this->time_limit = time_limit;
        best = now = init;
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
            double prob = get_prob();
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
