#pragma once
#include "../kyopro_library/base/include.hpp"
#include "../kyopro_library/base/macro.hpp"
#include "../kyopro_library/base/type.hpp"
#include "../kyopro_library/base/io.hpp"
#include "../kyopro_library/base/util.hpp"

void run();
void prep();
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
    prep();
#ifdef MULTI
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) {
#ifdef TDY
        cerr << "Case: #" << t + 1 << endl;
#endif
        run();
    }
#else
    run();
#endif
}

#ifdef DEBUG
#include "./debug.hpp"
#else
#define debug(...)
#define print_line
#endif
