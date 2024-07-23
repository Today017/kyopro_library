#pragma once
#include "../../kyopro_library/template.hpp"

struct Timer {
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point time_limit;
    Timer(ll time_limit_msec = 5000) {
		start = chrono::high_resolution_clock::now();
		time_limit = start + chrono::milliseconds(time_limit_msec * 1000);
	}
    inline ll get() const {
        auto now = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now - start).count();
    }
    inline bool check() const {
        return chrono::high_resolution_clock::now() < time_limit;
    }
};
