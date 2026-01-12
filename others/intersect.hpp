#include "../../kyopro_library/template.hpp"

///@brief 区間 [l1, r1) と [l2, r2) が交差しているか否かを返す
bool HaveIntersection(const ll l1, const ll r1, const ll l2, const ll r2) {
    return max(l1,l2)<min(r1,r2);
}
