#include "../../kyopro_library/template.cpp"

struct timer {
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point time_limit;
    timer(double time_limit_msec = 5000) : start(chrono::high_resolution_clock::now()) {
        time_limit = start + chrono::microseconds((long long)(time_limit_msec * 1e3));
    }
    double get() {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - start).count();
    }
    bool check() {
        auto now = chrono::high_resolution_clock::now();
        return now < time_limit;
    }
};