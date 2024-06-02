#include "../../kyopro_library/template.hpp"

template <typename T, typename Judge>
T binary_search(T ok, T ng, Judge judge) {
    while (abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        if (judge(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}
