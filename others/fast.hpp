#pragma once
/// @brief 高速化用の最適化 pragma
#ifndef TDY
#include <bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#endif