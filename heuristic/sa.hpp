#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/timer.hpp"
#include "../../kyopro_library/others/random.hpp"

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