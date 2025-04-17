#include"../../kyopro_library/template.hpp"

/// @file offset_vector.hpp
/// @brief 負の添字を取れる vector
template<typename T>
struct OffsetVector:vector<T>{
    int offset=0;
    OffsetVector()=default;

    /// @brief 添字として区間 [lo, hi] の値を取れる配列を宣言する
    /// @param init 初期値
    OffsetVector(int lo,int hi,T init){
        assert(lo<=hi);
        this->assign(hi-lo+1,init);
        offset=-lo;
    }

    T&operator[](int i){
        assert(i+offset>=0);
        return vector<T>::operator[](i+offset);
    }
    
    T operator[](int i)const{
        assert(i+offset>=0);
        return vector<T>::operator[](i+offset);
    }
};
