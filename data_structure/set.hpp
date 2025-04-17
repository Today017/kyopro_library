#include"../../kyopro_library/template.hpp"

/// @brief std::set ラッパー
template<typename T>
struct Set:set<T>{
    using set<T>::set;
    T not_found;
    Set()=default;

    /// @brief コンストラクタ
    /// @param not_found 指定の値が見つからなかったときに返す値
    Set(T not_found=-1){ this->not_found=not_found; }

    /// @brief 最小値を返す
    T min(){
        if(this->empty()) return not_found;
        return*this->begin();
    }

    /// @brief 最大値を返す
    T max(){
        if(this->empty())return not_found;
        return*this->rbegin();
    }

    /// @brief 最小値を返し、削除する
    T pop_min(){
        if(this->empty()) return not_found;
        T ret=min();
        this->erase(ret);
        return ret;
    }

    /// @brief 最大値を返し、削除する
    T pop_max(){
        if(this->empty()) return not_found;
        T ret=max();
        this->erase(ret);
        return ret;
    }

    /// @brief x が含まれているか否かを返す
    bool contains(T x){
        return this->find(x)!=this->end();
    }

    /// @brief x を削除する
    /// @brief x が含まれていたか否かを返す
    bool discard(T x){
        auto itr=this->find(x);
        if(itr==this->end()) return false;
        this->erase(itr);
        return true;
    }

    /// @brief x より大きい最小の値を返す
    T gt(T x){
        auto itr=this->upper_bound(x);
        if(itr==this->end()) return not_found;
        return*itr;
    }

    /// @brief x 以上の最小の値を返す
    T ge(T x){
        auto itr=this->lower_bound(x);
        if(itr==this->end()) return not_found;
        return*itr;
    }

    /// @brief x 以下の最大の値を返す
    T le(T x){
        auto itr=this->upper_bound(x);
        if(itr==this->begin()) return not_found;
        return*prev(itr);
    }

    /// @brief x 未満の最大値の値を返す
    T lt(T x){
        auto itr=this->lower_bound(x);
        if(itr==this->begin()) return not_found;
        return*prev(itr);
    }
};