#include"../../kyopro_library/template.hpp"

///@brief Deque
template<typename T>
struct Deque {
    Deque(int cap=2): head(0), tail(0), sz(0), cap(cap), dat(cap) {}

    void extend() {
        int ncap=cap*2;
        vector<T> ndat(ncap);
        rep(i,sz) ndat[i]=(*this)[i];
        dat=move(ndat);
        head=0; tail=sz;
        cap=ncap;
    }

    void push_back(const T& x) {
        if(sz==cap) extend();
        dat[tail]=x;
        tail=(tail+1==cap)? 0: tail+1;
        sz++;
    }

    void push_front(const T& x) {
        if(sz==cap) extend();
        head=(head==0)? cap-1: head-1;
        dat[head]=x;
        sz++;
    }

    void pop_front() {
        assert(!empty());
        head=(head+1==cap)? 0: head+1;
        sz--;
    }

    void pop_back() {
        assert(!empty());
        tail=(tail==0)? cap-1: tail-1;
        sz--;
    }

    T& operator[](int i) {
        int idx=head+i;
        if(idx>=cap) idx-=cap;
        return dat[idx];
    }

    const T& operator[](int i) const {
        int idx=head+i;
        if(idx>=cap) idx-=cap;
        return dat[idx];
    }

    T& front() { return dat[head]; }
    T& back() { return dat[(tail==0)? cap-1: tail-1]; }

    bool empty() const { return sz==0; }
    int size() const { return sz; }

private:
    vector<T> dat;
    int head, tail, sz, cap;
};
