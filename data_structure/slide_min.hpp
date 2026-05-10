#include"../../kyopro_library/template.hpp"

template<typename T, bool MIN=true>
struct SlideMin {
    SlideMin()=default;

    void push(T x) {
        while(!dq.empty() && !cmp(dq.back().first,x)) dq.pop_back();
        dq.push_back({x,r++}); siz++;
    }

    void pop() {
        if(dq.front().second==l) dq.pop_front();
        l++; siz--;
    }

    T fold() const { return dq.front().first; }

    int size() const { return siz; }

private:
    int l=0, r=0, siz=0;
    deque<pair<T,int>> dq;

    bool cmp(const T& x, const T& y) {
        if(MIN) return x<y;
        return x>y;
    }
};
