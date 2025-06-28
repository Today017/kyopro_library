#include"../../kyopro_library/template.hpp"

/// @brief 削除可能な優先度付きキュー
/// @tparam MAX trueのとき、最大値を返す
/// @tparam NONE 空のときに返す値
template<typename T, bool MAX=true, T NONE=-INF>
struct ErasablePQ {
    priority_queue<T> pq, pq2;
    int siz=0;

    ErasablePQ() { siz=0; }

    /// @brief x を追加する
    void push(int x) {
        if(!MAX) x=-x;
        pq.push(x);
        siz++;
    }

    /// @brief x を削除する
    void erase(int x) {
        if(!MAX) x=-x;
        pq2.push(x);
        siz--;
    }

    /// @brief 最大値を返す
    T top() {
        while(!pq.empty()) {
            if(pq2.empty()) return (MAX ? pq.top() : -pq.top());
            if(pq.top()==pq2.top()) {
                pq.pop();
                pq2.pop();
            } else {
                return (MAX ? pq.top() : -pq.top());
            }
        }

        return NONE;
    }
};
