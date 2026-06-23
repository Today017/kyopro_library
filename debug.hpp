#pragma once
#include "../kyopro_library/data_structure/fenwick_tree.hpp"
#include "../kyopro_library/data_structure/fenwick_tree_abel.hpp"
#include "../kyopro_library/data_structure/segtree.hpp"
#include "../kyopro_library/data_structure/segtree_lazy.hpp"
#include "../kyopro_library/data_structure/segtree_act.hpp"
#include "../kyopro_library/graph/dsu.hpp"
// #include "../kyopro_library/others/int128.hpp"
#include "../atcoder/modint"
#include "../atcoder/segtree"
#include "../atcoder/lazysegtree"
#include "../atcoder/fenwicktree"
#include "../atcoder/dsu"

// デバッグ出力は operator<< に依存せず、専用の dmp() を通して整形する。
// これにより、答え出力用 (cout) の operator<< とは独立に、
// デバッグ用 (cerr) では角括弧形式の見やすい出力ができる。
namespace TdyDebug {
    // 角括弧形式で出力したい「反復可能」な型 (vector/set/map/array など)。
    // string 系は専用オーバーロードで扱うため概念上含めても優先されない。
    template <typename T>
    concept Iterable = requires(const T& a) {
        std::begin(a);
        std::end(a);
    };

    // ---- 前方宣言 ----
    template <typename T>
    void dmp(ostream& os, const T& x);
    void dmp(ostream& os, const string& s);
    void dmp(ostream& os, const basic_string<bool>& a);
    template <typename A, typename B>
    void dmp(ostream& os, const pair<A, B>& p);
    template <typename... Ts>
    void dmp(ostream& os, const tuple<Ts...>& t);
    template <Iterable T>
    void dmp(ostream& os, const T& a);
    template <typename T>
    void dmp(ostream& os, queue<T> a);
    template <typename T>
    void dmp(ostream& os, priority_queue<T> a);
    template <typename T>
    void dmp(ostream& os, priority_queue<T, vector<T>, greater<T>> a);
    void dmp(ostream& os, atcoder::modint998244353 a);
    void dmp(ostream& os, atcoder::modint1000000007 a);
    template <typename T, T (*op)(T, T), T (*e)()>
    void dmp(ostream& os, atcoder::segtree<T, op, e> a);
    template <typename T, T (*op)(T, T), T (*e)(), typename F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
    void dmp(ostream& os, atcoder::lazy_segtree<T, op, e, F, mapping, composition, id> a);
    template <typename T>
    void dmp(ostream& os, atcoder::fenwick_tree<T> a);
    void dmp(ostream& os, FenwickTree a);
    template <typename T>
    void dmp(ostream& os, FenwickTreeAbel<T> a);
    template <typename T>
    void dmp(ostream& os, SegTree<T> a);
    template <typename T, typename U, auto M>
    void dmp(ostream& os, SegTreeLazy<T, U, M> a);
    template <typename T>
    void dmp(ostream& os, SegTreeAct<T> a);

    // ---- 定義 ----
    // 既定: それ以外の型 (int, ll, double, ModInt など operator<< を持つ型) はそのまま出力。
    template <typename T>
    void dmp(ostream& os, const T& x) { os << x; }

    void dmp(ostream& os, const string& s) { os << s; }

    void dmp(ostream& os, const basic_string<bool>& a) {
        os << "[";
        for(size_t i = 0; i < a.size(); i++) {
            os << (a[i] ? "o" : "x");
            if(i + 1 != a.size()) os << ",";
        }
        os << "]";
    }

    template <typename A, typename B>
    void dmp(ostream& os, const pair<A, B>& p) {
        os << "(";
        dmp(os, p.first);
        os << ",";
        dmp(os, p.second);
        os << ")";
    }

    template <typename... Ts>
    void dmp(ostream& os, const tuple<Ts...>& t) {
        os << "(";
        bool first = true;
        apply([&](const auto&... xs) { ((os << (first ? "" : ","), first = false, dmp(os, xs)), ...); }, t);
        os << ")";
    }

    template <Iterable T>
    void dmp(ostream& os, const T& a) {
        os << "[";
        bool first = true;
        for(const auto& x : a) {
            if(!first) os << ",";
            first = false;
            dmp(os, x);
        }
        os << "]";
    }

    template <typename T>
    void dmp(ostream& os, queue<T> a) {
        os << "[";
        bool first = true;
        while(!a.empty()) {
            if(!first) os << ",";
            first = false;
            dmp(os, a.front());
            a.pop();
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, priority_queue<T> a) {
        os << "[";
        bool first = true;
        while(!a.empty()) {
            if(!first) os << ",";
            first = false;
            dmp(os, a.top());
            a.pop();
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, priority_queue<T, vector<T>, greater<T>> a) {
        os << "[";
        bool first = true;
        while(!a.empty()) {
            if(!first) os << ",";
            first = false;
            dmp(os, a.top());
            a.pop();
        }
        os << "]";
    }

    void dmp(ostream& os, atcoder::modint998244353 a) { os << a.val(); }
    void dmp(ostream& os, atcoder::modint1000000007 a) { os << a.val(); }

    template <typename T, T (*op)(T, T), T (*e)()>
    void dmp(ostream& os, atcoder::segtree<T, op, e> a) {
        int n = a.get_size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a.prod(i, i + 1));
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T, T (*op)(T, T), T (*e)(), typename F, T (*mapping)(F, T), F (*composition)(F, F), F (*id)()>
    void dmp(ostream& os, atcoder::lazy_segtree<T, op, e, F, mapping, composition, id> a) {
        int n = a.get_size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a.get(i));
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, atcoder::fenwick_tree<T> a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a.sum(i, i + 1));
            if(i != n - 1) os << ",";
        }
        os << "]";
    }

    void dmp(ostream& os, FenwickTree a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a[i]);
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, FenwickTreeAbel<T> a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a[i]);
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, SegTree<T> a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a[i]);
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T, typename U, auto M>
    void dmp(ostream& os, SegTreeLazy<T, U, M> a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a[i]);
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
    template <typename T>
    void dmp(ostream& os, SegTreeAct<T> a) {
        int n = a.size();
        os << "[";
        for(int i = 0; i < n; i++) {
            dmp(os, a[i]);
            if(i != n - 1) os << ",";
        }
        os << "]";
    }
}  // namespace TdyDebug

#define print_line cerr << "--------------------" << __LINE__ << "--------------------" << endl;
#define debug(...) DebugPrint(0, #__VA_ARGS__, __VA_ARGS__)
#define getName(VariableName) #VariableName

template <typename T>
void DebugPrint(int i, T name) { cerr << endl; }
template <typename T1, typename T2, typename... T3>
void DebugPrint(int i, const T1& name, const T2& a, const T3&... b) {
    cerr << "\033[31m";
    int tmp = 0;
    while(true) {
        if(name[i] == '\0') break;
        if(tmp == 0 && name[i] == ',') break;
        cerr << name[i];
        if(name[i] == '(') tmp++;
        else if(name[i] == ')') tmp--;
        i++;
    }
    cerr << "\033[32m";
    cerr << ":";
    TdyDebug::dmp(cerr, a);
    cerr << ",";
    cerr << "\033[0m";
    DebugPrint(i + 1, name, b...);
}
