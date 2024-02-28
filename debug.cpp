#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
#include "../kyopro_library/data_structure/fen.cpp"
#include "../kyopro_library/data_structure/segt.cpp"
#include "../kyopro_library/data_structure/segtlz.cpp"
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<vector<T>>> &A) {
    int I = A.size();
    int J = A.front().size();
    int K = A.front().front().size();
    os << "[\n";
    for (int i = 0; i < I; i++) {
        os << "   " << i << " :[\n";
        for (int j = 0; j < J; j++) {
            os << "      " << j << " :[ ";
            for (int k = 0; k < K; k++) {
                os << A[i][j][k];
                if (k != K - 1) {
                    os << ", ";
                }
            }
            os << "]\n";
        }
        os << "   ]\n";
    }
    os << " ]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &A) {
    os << "[\n";
    int I = A.size();
    int J = A.front().size();
    for (int i = 0; i < I; i++) {
        os << "   " << i << " :[";
        for (int j = 0; j < J; j++) {
            os << A[i][j];
            if (j != J - 1) {
                os << ", ";
            }
        }
        os << "]\n";
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &A) {
    int n = A.size();
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << A[i];
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &A) {
    int n = A.size();
    os << "[ ";
    for (T x : A) {
        os << x << ", ";
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &A) {
    int n = A.size();
    os << "[ ";
    for (T x : A) {
        os << x << ", ";
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &A) {
    int n = A.size();
    os << "[ ";
    for (T x : A) {
        os << x << ", ";
    }
    os << "]";
    return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
    os << "( " << p.first << ", " << p.second << " )";
    return os;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const map<T1, T2> &A) {
    os << "[ ";
    for (pair<T1, T2> x : A) {
        os << x << ", ";
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, queue<T> A) {
    int n = A.size();
    os << "[ ";
    while (!A.empty()) {
        os << A.front() << ", ";
        A.pop();
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, priority_queue<T> A) {
    int n = A.size();
    os << "[ ";
    while (!A.empty()) {
        os << A.top() << ", ";
        A.pop();
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, atcoder::fenwick_tree<T> A) {
    int n = A._n;
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << A.sum(i, i + 1);
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, fenwick_tree<T> A) {
    int n = A.n;
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << A.sum[i];
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template <typename S, S (*op)(S, S), S (*e)()>
ostream &operator<<(ostream &os, atcoder::segtree<S, op, e> A) {
    int n = A._n;
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << A.prod(i, i + 1);
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << " ]";
    return os;
}
template <typename T>
ostream &operator<<(ostream &os, segment_tree<T> a) {
    int n = a.size;
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << a[i];
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
template <typename T, typename U>
ostream &operator<<(ostream &os, segment_tree_lazy<T, U> a) {
    int n = a.size;
    os << "[ ";
    for (int i = 0; i < n; i++) {
        os << a[i];
        if (i != n - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
ostream &operator<<(ostream &os, atcoder::dsu ds) {
    os << ds.groups();
    return os;
}
ostream &operator<<(ostream &os, atcoder::modint998244353 x) {
    os << x.val();

    return os;
}
ostream &operator<<(ostream &os, atcoder::modint1000000007 x) {
    os << x.val();
    return os;
}

#define print_line cerr << "--------------------" << __LINE__ << "--------------------" \
                        << "\n"
#define debug(...) debug_print(0, #__VA_ARGS__, __VA_ARGS__)
#define get_name(VariableName) #VariableName
template <typename T>
void debug_print(int i, T name) {
    cerr << endl;
}
template <typename T1, typename T2, typename... T3>
void debug_print(int i, const T1 &name, const T2 &a, const T3 &...b) {
    cerr << "\033[31m";
    for (; name[i] != ',' && name[i] != '\0'; i++) {
        cerr << name[i];
    }
    cerr << "\033[32m";
    cerr << " : " << a << ", ";
    cerr << "\033[0m";
    debug_print(i + 1, name, b...);
}
