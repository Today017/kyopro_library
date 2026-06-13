#pragma once
#include"../../kyopro_library/template.hpp"

///@brief Simple Queue
template<typename T>
struct Queue {
    Queue() {}
    void push(const T& x) { dat.push_back(x); }
    T pop() { return dat[cur++]; }
    T& front() { return dat[cur]; }
    int size() { return dat.size()-cur; }
    bool empty() { return cur==dat.size(); }
    void clear() { dat.clear(); cur=0; }

private:
    vector<T> dat;
    int cur=0;
};
