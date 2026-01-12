#include"../../kyopro_library/template.hpp"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
struct SortedTree:tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update> {
    using tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>::tree;
    T not_found=-1;
    SortedTree()=default;

    ///@brief コンストラクタ
    ///@param not_found 指定の値が見つからなかったときに返す値
    SortedTree(T not_found=-1) { this->not_found=not_found; }

    ///@brief 最小値を返す
    T min() {
        if(this->empty()) return not_found;
        return*this->begin();
    }

    ///@brief 最大値を返す
    T max() {
        if(this->empty()) return not_found;
        return*this->rbegin();
    }

    ///@brief 最小値を返し、削除する
    T pop_min() {
        if(this->empty()) return not_found;
        T ret=min(); this->erase(ret);
        return ret;
    }

    ///@brief 最大値を返し、削除する
    T pop_max() {
        if(this->empty()) return not_found;
        T ret=max(); this->erase(ret);
        return ret;
    }

    ///@brief x が含まれているか否かを返す
    bool contains(T x) { return this->find(x)!=this->end(); }

    ///@brief x を削除する
    bool discard(T x) {
        auto itr=this->find(x);
        if(itr==this->end()) return false;
        this->erase(itr);
        return true;
    }

    ///@brief x より大きい最小の値を返す
    T gt(T x) {
        auto itr=this->upper_bound(x);
        if(itr==this->end()) return not_found;
        return *itr;
    }

    ///@brief x 以上最小の値を返す
    T ge(T x) {
        auto itr=this->lower_bound(x);
        if(itr==this->end()) return not_found;
        return *itr;
    }

    ///@brief x 未満最大の値を返す
    T lt(T x) {
        auto itr=this->lower_bound(x);
        if(itr==this->begin()) return not_found;
        return *--itr;
    }

    ///@brief x 以下の最大の値を返す
    T le(T x) {
        auto itr=this->upper_bound(x);
        if(itr==this->begin()) return not_found;
        return *--itr;
    }

    ///@brief x より小さい値の個数を返す
    int count_lt(T x) { return this->order_of_key(x); }

    ///@brief x 以下の値の個数を返す
    int count_le(T x) { return this->order_of_key(x+1); }

    ///@brief x より大きい値の個数を返す
    int count_gt(T x) { return this->size()-this->order_of_key(x+1); }

    ///@brief x 以上の値の個数を返す
    int count_ge(T x) { return this->size()-this->order_of_key(x); }

    ///@brief k(0-indexed) 番目に小さい値の個数を返す
    T kth_min(int k) { return *this->find_by_order(k); }

    ///@brief k(0-indexed) 番目に大きい値の個数を返す
    T kth_max(int k) { return *this->find_by_order(this->size()-k-1); }
};
