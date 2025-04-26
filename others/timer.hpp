#pragma once
#include"../../kyopro_library/template.hpp"

/// @brief タイマー
struct Timer {
    Timer(ll time_limit_msec=5000) {
        start=chrono::high_resolution_clock::now();
        time_limit=start+chrono::milliseconds(time_limit_msec);
    }

    /// @brief 今の時間 msec を返す
    inline ll get() const {
        auto now=chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(now-start).count();
    }

    /// @brief 今が制限時間内であるかを返す
    inline bool check() const {
        return chrono::high_resolution_clock::now()<time_limit;
    }

private:
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point time_limit;
};
