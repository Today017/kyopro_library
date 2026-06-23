#pragma once
#include "../../kyopro_library/template.hpp"

/// @brief スライドモノイド積
template <typename Semigroup>
struct QueueFoldable {
    using Type = typename Semigroup::Type;

    void push(const Type& x) {
        if(back.empty()) back.push_back({x, x});
        else back.push_back({x, Semigroup::op(back.back().second, x)});
    }

    void pop() {
        if(front.empty()) {
            Type x = back.back().first;
            back.pop_back();
            front.push_back({x, x});
            while(!back.empty()) {
                x = back.back().first;
                back.pop_back();
                front.push_back({x, Semigroup::op(x, front.back().second)});
            }
        }
        front.pop_back();
    }

    bool empty() const { return front.empty() && back.empty(); }

    Type fold() const {
        if(front.empty()) return back.back().second;
        if(back.empty()) return front.back().second;
        return Semigroup::op(front.back().second, back.back().second);
    }

    int size() const { return front.size() + back.size(); }

private:
    vector<pair<Type, Type>> front, back;
};

#include "../../kyopro_library/others/monoid.hpp"
