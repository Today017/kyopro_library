#include "../../kyopro_library/template.hpp"

template <typename T>
struct NegativeVector : vector<T> {
    int offset;
    NegativeVector(int lo, int hi, T init) {
        assert(lo <= hi);
        this->assign(hi - lo + 1, init);
        offset = -lo;
    }
    T& operator[](int i) {
        assert(i + offset >= 0);
        return vector<T>::operator[](i + offset);
    }
    T operator[](int i) const {
        assert(i + offset >= 0);
        return vector<T>::operator[](i + offset);
    }
};