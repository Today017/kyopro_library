#pragma once

#define rep1(n) for(ii i = 0; i < (n); i++)
#define rep2(i, n) for(ii i = 0; i < (n); i++)
#define rep3(i, a, b) for(ii i = (a); i < (b); i++)
#define rep4(i, a, b, c) for(ii i = (a); i < (b); i += (c))
#define rep_overload(a, b, c, d, e, ...) e
#define rep(...) rep_overload(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)

#define per1(n) for(ii i = (n) - 1; i >= 0; i--)
#define per2(i, n) for(ii i = (n) - 1; i >= 0; i--)
#define per3(i, a, b) for(ii i = (b) - 1; i >= (a); i--)
#define per4(i, a, b, c) for(ii i = (b) - 1; i >= (a); i -= (c))
#define per_overload(a, b, c, d, e, ...) e
#define per(...) per_overload(__VA_ARGS__, per4, per3, per2, per1)(__VA_ARGS__)

#define fore(x, a) for(auto &x : a)

#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

#define QYN(q, a, b) ((q) ? (a) : (b))

#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define mkt make_tuple
#define fi first
#define se second

#define vv(type, name, a, ...) \
    vector<vector<type>> name(a, vector<type>(__VA_ARGS__))
#define vvv(type, name, a, b, ...)     \
    vector<vector<vector<type>>> name( \
        a, vector<vector<type>>(b, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)         \
    vector<vector<vector<vector<type>>>> name( \
        a, vector<vector<vector<type>>>(       \
               b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))
#define vvvvv(type, name, a, b, c, d, ...)             \
    vector<vector<vector<vector<vector<type>>>>> name( \
        a, vector<vector<vector<vector<type>>>>(       \
               b, vector<vector<vector<type>>>(        \
                      c, vector<vector<type>>(d, vector<type>(__VA_ARGS__)))))

#define applyv(v, f)      \
    [&]() {               \
        auto &&_v = (v);  \
        for(auto &x : _v) \
            f(x);         \
    }()
#define mapv(v, f)                                           \
    [&]() {                                                  \
        auto &&_v = (v);                                     \
        using Type = std::decay_t<decltype(f(*_v.begin()))>; \
        std::vector<Type> ret;                               \
        ret.reserve(_v.size());                              \
        for(const auto &x : _v)                              \
            ret.push_back(f(x));                             \
        return ret;                                          \
    }()

#define II(...)     \
    ii __VA_ARGS__; \
    input(__VA_ARGS__)
#define LL(...)     \
    ll __VA_ARGS__; \
    input(__VA_ARGS__)
#define IDX(...)        \
    ii __VA_ARGS__;     \
    input(__VA_ARGS__); \
    input_index(__VA_ARGS__)
#define STR(...)        \
    string __VA_ARGS__; \
    input(__VA_ARGS__);
#define CHR(...)      \
    char __VA_ARGS__; \
    input(__VA_ARGS__);
#define LD(...)     \
    ld __VA_ARGS__; \
    input(__VA_ARGS__);
#define VI(A, N)     \
    vector<ii> A(N); \
    input(A);
#define VVI(A, N, M)                        \
    vector<vector<ii>> A(N, vector<ii>(M)); \
    input(A);
#define VL(A, N)     \
    vector<ll> A(N); \
    input(A);
#define VVL(A, N, M)                        \
    vector<vector<ll>> A(N, vector<ll>(M)); \
    input(A);
#define VPI(A, N) \
    vpi A(N);     \
    input(A);
#define VTI(A, N) \
    vti A(N);     \
    input(A);
#define VI2(A, B, N)       \
    vector<ii> A(N), B(N); \
    rep(i, N) cin >> A[i] >> B[i];
#define VL2(A, B, N)       \
    vector<ll> A(N), B(N); \
    rep(i, N) cin >> A[i] >> B[i];
#define VI3(A, B, C, N)          \
    vector<ii> A(N), B(N), C(N); \
    rep(i, N) cin >> A[i] >> B[i] >> C[i];
#define VL3(A, B, C, N)          \
    vector<ll> A(N), B(N), C(N); \
    rep(i, N) cin >> A[i] >> B[i] >> C[i];
#define VST(A, N)        \
    vector<string> A(N); \
    input(A);
#define IN2(A, B) rep(i, siz(A)) cin >> A[i] >> B[i];
#define IN3(A, B, C) rep(i, siz(A)) cin >> A[i] >> B[i] >> C[i];
#define IN4(A, B, C, D) rep(i, siz(A)) cin >> A[i] >> B[i] >> C[i] >> D[i];
#define IN5(A, B, C, D, E) \
    rep(i, siz(A)) cin >> A[i] >> B[i] >> C[i] >> D[i] >> E[i];
