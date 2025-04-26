#include"../../kyopro_library/template.hpp"

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
struct SortedMultiTree:tree<pair<T,int>,null_type,less<pair<T,int>>,rb_tree_tag,tree_order_statistics_node_update> {
    using tree<pair<T,int>,null_type,less<pair<T,int>>,rb_tree_tag,tree_order_statistics_node_update>::tree;
    using P=pair<T,int>;
    T not_found=-1;
    SortedMultiTree()=default;

    /// @brief コンストラクタ
    /// @param not_found 指定の値が見つからなかったときに返す値
    SortedMultiTree(T not_found=-1) { this->not_found=not_found; }

	/// @brief x を追加する
    void add(T x) {
        if(this->size()==0) {
            this->insert(P{x,0});
            return;
        }
        auto itr=this->lower_bound(P{x+1,0});
        if(itr==this->begin()) {
            this->insert(P{x,0});
            return;
        }
        itr--;
        if(itr->first!=x) {
            this->insert(P{x,0});
            return;
        }
        this->insert(P{x,itr->second+1});
    }

    /// @brief 最小値を返す
    T min() {
        if(this->empty())return not_found;
        return*this->begin()->first;
    }

    /// @brief 最大値を返す
    T max() {
        if(this->empty())return not_found;
        return*this->rbegin()->first;
    }

    /// @brief 最小値を返し、削除する
    T pop_min() {
        if(this->empty())return not_found;
        auto mn=*this->begin();
        T ret=mn.first;
        this->erase(mn);
        return ret;
    }

    /// @brief 最大値を返し、削除する
    T pop_max() {
        if(this->empty())return not_found;
        auto mx=*this->rbegin();
        T ret=mx.first;
        this->erase(mx);
        return ret;
    }

    /// @brief x が含まれているか否かを返す
    bool contains(T x) {
        auto itr=this->lower_bound({x,0});
        if(itr==this->end())return false;
        return itr->first==x;
    }

	/// @brief x の個数を返す
    int count(T x) {
        if(!contains(x))return 0;
        auto itr=this->lower_bound({x+1,0});
        itr--;
        return itr->second+1;
    }

    /// @brief x を削除する
	/// @brief x が含まれていたか否かを返す
    bool discard(T x) {
        if(!contains(x))return false;
        auto itr=prev(this->lower_bound({x+1,0}));
        if(itr==this->end())return false;
        this->erase(itr);
        return true;
    }

	/// @brief x より大きい最小の値を返す
    T gt(T x) {
        auto itr=this->lower_bound({x+1,0});
        if(itr==this->end())return not_found;
        return itr->first;
    }

	/// @brief x 以上最小の値を返す
    T ge(T x) {
        auto itr=this->lower_bound({x,0});
        if(itr==this->end())return not_found;
        return itr->first;
    }

	/// @brief x 未満最大の値を返す
    T lt(T x) {
        auto itr=this->lower_bound({x,0});
        if(itr==this->begin())return not_found;
        return(--itr)->first;
    }

	/// @brief x 以下最大の値を返す
    T le(T x) {
        auto itr=this->lower_bound({x+1,0});
        if(itr==this->begin())return not_found;
        return(--itr)->first;
    }

    /// @brief x 未満の値の個数を返す
    int count_lt(T x) { return this->order_of_key({x,0}); }

    /// @brief x 以下の値の個数を返す
    int count_le(T x) { return this->order_of_key({x+1,0}); }

    /// @brief x より大きい値の個数を返す
    int count_gt(T x) { return this->size()-this->order_of_key({x+1,0}); }

    /// @brief x 以上の値の個数を返す
    int count_ge(T x) { return this->size()-this->order_of_key({x,0}); }

    /// @brief k(0-indexed) 番目に小さい値の個数を返す
    T kth_min(int k) { return this->find_by_order(k)->first; }

    /// @brief k(0-indexed) 番目に大きい値の個数を返す
    T kth_max(int k) { return this->find_by_order(this->size()-k-1)->first; }
};