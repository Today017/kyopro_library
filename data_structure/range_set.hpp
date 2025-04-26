#include"../../kyopro_library/template.hpp"

/// @brief 区間を set で管理するデータ構造
/// @ref verify:https://yukicoder.me/submissions/1021763
struct RangeSet {
    set<PL> dat;
    RangeSet() {
        dat.insert({-INFL,-INFL});
        dat.insert({INFL,INFL});
    }

    /// @brief 区間 [l, r) を追加する
    void insert(ll l, ll r) {
        assert(l<r);
        auto it=dat.lower_bound({l,0});
        if(it!=dat.begin()) {
            it--;
            if(it->second>=l) {
                l=it->first;
                r=max(r,it->second);
                it=dat.erase(it);
            } else {
                it++;
            }
        }
        while(it!=dat.end()&&it->first<=r) {
            r=max(r,it->second);
            it=dat.erase(it);
        }
        dat.insert({l,r});
    }

    /// @brief 区間 [l, r) を削除する
    void erase(ll l, ll r) {
        assert(l<r);
        auto it=dat.lower_bound({l,0});
        if(it!=dat.begin()) {
            it--;
            if(it->second>l) {
                ll L=it->first,R=it->second;
                it=dat.erase(it);
                if(L<l) dat.insert({L,l});
                if(r<R) dat.insert({r,R});
            }else{
                it++;
            }
        }
        while(it!=dat.end()&&it->first<r) {
            ll L=it->first,R=it->second;
            it=dat.erase(it);
            if(L<l) dat.insert({L,l});
            if(r<R) dat.insert({r,R});
        }
    }

    /// @brief 区間 [l, r) が完全に被覆されているかどうかを判定する
    /// @attention unverified
    bool is_covered(ll l, ll r) {
        auto it=dat.upper_bound({l,INFL});
        if(it==dat.begin()) return false;
        it--;
        return it->first<=l&&r<=it->second;
    }

    /// @brief 点 x を含む区間を返す
    /// @brief 存在しない場合は `{-INFL, -INFL}` を返す
    PL covering_range(ll x) {
        if(!is_covered(x,x+1)) return{-INFL,-INFL};
        auto it=dat.upper_bound({x,INFL});
        it--;
        return*it;
    }
};