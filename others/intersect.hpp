#include "../../kyopro_library/template.hpp"

bool haveIntersection(const ll l1, const ll r1, const ll l2, const ll r2) {
    return max(l1, l2) <= min(r1, r2);
}
