#include "../../kyopro_library/template.hpp"

struct ArithmeticProgression {
    ll start = INFL;
    ll goal = INFL;
    ll step = INFL;
    ll length = INFL;
    void normalize() {
        int undef_cnt = 0;
        if (start == INFL) undef_cnt++;
        if (goal == INFL) undef_cnt++;
        if (step == INFL) undef_cnt++;
        if (length == INFL) undef_cnt++;
        assert(undef_cnt <= 1);
        if (goal == INFL) {
            goal = start + (length - 1) * step;
        } else if (start == INFL) {
            start = goal - (length - 1) * step;
        } else if (step == INFL) {
            step = (start == goal) ? 0 : (goal - start) / (length - 1);
        } else if (length == INFL) {
            assert(step != 0);
            length = (goal - start) / step + 1;
        }
    }
};

ll arithmeticSum(ArithmeticProgression ap) {
    ap.normalize();
    return (ap.start + ap.goal) * ap.length / 2;
}
