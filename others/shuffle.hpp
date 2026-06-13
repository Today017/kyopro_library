#pragma once
#include"../../kyopro_library/template.hpp"

///@brief シャッフル
template<typename T>
void Shuffle(vector<T>& V) { shuffle(all(V),mt19937(random_device{}())); }
