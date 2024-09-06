#include "../../kyopro_library/template.hpp"

struct ArithmeticProgression {
    ll start = INFL;
    ll goal = INFL;
    ll step = INFL;
    ll length = INFL;
};

ll arithmeticSum(ArithmeticProgression ap) {
    int undef_cnt = 0;
    if (ap.start == INFL) undef_cnt++;
    if (ap.goal == INFL) undef_cnt++;
    if (ap.step == INFL) undef_cnt++;
    if (ap.length == INFL) undef_cnt++;
    assert(undef_cnt <= 1);
    if (ap.goal == INFL) {
        ap.goal = ap.start + (ap.length - 1) * ap.step;
    } else if (ap.start == INFL) {
        ap.start = ap.goal - (ap.length - 1) * ap.step;
    } else if (ap.step == INFL) {
        ap.step = (ap.start == ap.goal) ? 0 : (ap.goal - ap.start) / (ap.length - 1);
    } else if (ap.length == INFL) {
        assert(ap.step != 0);
        ap.length = (ap.goal - ap.start) / ap.step + 1;
    }
    return (ap.start + ap.goal) * ap.length / 2;
}
