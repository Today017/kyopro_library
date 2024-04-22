#pragma once
#include "../../kyopro_library/template.hpp"
#include "../../kyopro_library/others/timer.hpp"
#include "../../kyopro_library/others/random.hpp"

template<typename Data>
struct climbing {
    timer t;
    Data best, now;
    climbing(ll time_limit) {
        t = timer(time_limit);
        now.init();
    }
    Data run() {
        while(t.check()) {
            ll next_score = now.get_next_score();
            ll now_score = now.get_score();
            if(next_score > now_score) {
                now.modify();
                if(now.get_score() > best.get_score()) {
                    best.record(now);
                }
            }
        }
        return best;
    }
};