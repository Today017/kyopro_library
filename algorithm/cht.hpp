#include"../../kyopro_library/template.hpp"
#include"../../kyopro_library/algorithm/binary_search.hpp"

/// @brief Convex Hull Trick
/// @ref verify: https://judge.yosupo.jp/submission/291811
/// @ref https://hcpc-hokudai.github.io/archive/algorithm_convex_hull_trick_001.pdf
/// @tparam Min true のとき最小値を管理する
template<typename T=ll, bool MIN=true>
struct CHT {
    CHT()=default;

    /// @brief 直線 ax + b を追加する
    /// @note O(log(N))
    void add(T a, T b) {
        if(!MIN) a*=-1, b*=-1;

        if(lines.count(a) && lines[a]<=b) return;
        lines[a]=b;
        auto it=lines.find(a);
        if(!need(it)) {
            lines.erase(a);
            return;
        }
        if(it!=lines.begin()) {
            it=prev(it);
            while(true) {
                if(need(it)) break;
                auto prv=prev(it);
                lines.erase(it);
                it=prv;
            }
        }
        it=next(lines.find(a));
        while (true) {
            if(need(it)) break;
            auto nxt=next(it);
            lines.erase(it);
            it=nxt;
        }
    }

    /// @brief x に対する直線群の最小値を求める
    /// @note O((log(N))^2)
    T get(T x) {
        auto [a,b]=*lines.lower_bound(BinarySearch<T>(lines.begin()->first,lines.rbegin()->first+1,[&](T m) {
            auto it=lines.lower_bound(m);
            if(it==lines.begin()) return true;
            if(it==lines.end()) return false;
            auto [a1,b1]=*prev(it);
            auto [a2,b2]=*it;
            return a1*x+b1>a2*x+b2;
        }));
        return (a*x+b)*(MIN?1:-1);
    }

private:
    map<T,T> lines;
    bool need(const typename map<T,T>::iterator it) {
        if (it==lines.begin() || it==prev(lines.end()) || it==lines.end()) return true;
        auto prv=prev(it),nxt=next(it);
        auto [a,b]=*it;
        auto [a1,b1]=*nxt;
        auto [a2,b2]=*prv;
        return (__int128_t)(a1-a)*(b-b2)<(__int128_t)(a-a2)*(b1-b);
    }
};