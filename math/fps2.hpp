/// 【形式的冪級数】
/**
 * MFPS() : O(1)
 *	零多項式 f = 0 で初期化する．
 *
 * MFPS(mint c0) : O(1)
 *	定数多項式 f = c0 で初期化する．
 *
 * MFPS(mint c0, int n) : O(n)
 *	n 次未満の項をもつ定数多項式 f = c0 で初期化する．
 *
 * MFPS(vm c) : O(n)
 *	f(z) = c[0] + c[1] z + ... + c[n - 1] z^(n-1) で初期化する．
 *
 * set_conv(vm(*CONV)(const vm&, const vm&)) : O(1)
 *	畳込み用の関数を CONV に設定する．
 *
 * c + f, f + c : O(1)	f + g : O(n)
 * f - c : O(1)			c - f, f - g, -f : O(n)
 * c * f, f * c : O(n)	f * g : O(n log n)		f * g_sp : O(n |g|)
 * f / c : O(n)			f / g : O(n log n)		f / g_sp : O(n |g|)
 *	形式的冪級数としての和，差，積，商の結果を返す．
 *	g_sp はスパース多項式であり，{次数, 係数} の次数昇順の組の vector で表す．
 *	制約 : 商では g(0) != 0
 *
 * MFPS f.inv(int d) : O(n log n)
 *	1 / f mod z^d を返す．
 *	制約 : f(0) != 0
 *
 * MFPS f.quotient(MFPS g) : O(n log n)
 * MFPS f.reminder(MFPS g) : O(n log n)
 * pair<MFPS, MFPS> f.quotient_remainder(MFPS g) : O(n log n)
 *	多項式としての f を g で割った商，余り，商と余りの組を返す．
 *	制約 : g の最高次の係数は 0 でない
 *
 * int f.deg(), int f.size() : O(1)
 *	多項式 f の次数[項数]を返す．
 *
 * MFPS::monomial(int d, mint c = 1) : O(d)
 *	単項式 c z^d を返す．
 *
 * mint f.assign(mint c) : O(n)
 *	多項式 f の不定元 z に c を代入した値を返す．
 *
 * f.resize(int d) : O(1)
 *	mod z^d をとる．
 *
 * f.resize() : O(n)
 *	不要な高次の項を削る．
 *
 * f >> d, f << d : O(n)
 *	係数列を d だけ右[左]シフトした多項式を返す．
 *  （右シフトは z^d の乗算，左シフトは z^d で割った商と等価）
 *
 * f.push_back(c) : O(1)
 *	最高次の係数として c を追加する．
 */
struct MFPS {
    using SMFPS = vector<pim>;

    int n;  // 係数の個数（次数 + 1）
    vm c;  // 係数列
    inline static vm (*CONV)(const vm&, const vm&) = convolution;  // 畳込み用の関数

    // コンストラクタ（0，定数，係数列で初期化）
    MFPS() : n(0) {}
    MFPS(mint c0) : n(1), c({c0}) {}
    MFPS(int c0) : n(1), c({mint(c0)}) {}
    MFPS(mint c0, int d) : n(d), c(n) { c[0] = c0; }
    MFPS(int c0, int d) : n(d), c(n) { c[0] = c0; }
    MFPS(const vm& c_) : n(sz(c_)), c(c_) {}
    MFPS(const vi& c_) : n(sz(c_)), c(n) { rep(i, n) c[i] = c_[i]; }

    // 代入
    MFPS(const MFPS& f) = default;
    MFPS& operator=(const MFPS& f) = default;
    MFPS& operator=(const mint& c0) {
        n = 1;
        c = {c0};
        return *this;
    }

    void push_back(mint cn) {
        c.emplace_back(cn);
        ++n;
    }
    void pop_back() {
        c.pop_back();
        --n;
    }
    [[nodiscard]] mint back() { return c.back(); }

    // 比較
    [[nodiscard]] bool operator==(const MFPS& g) const { return c == g.c; }
    [[nodiscard]] bool operator!=(const MFPS& g) const { return c != g.c; }

    // アクセス
    inline mint const& operator[](int i) const { return c[i]; }
    inline mint& operator[](int i) { return c[i]; }

    // 次数
    [[nodiscard]] int deg() const { return n - 1; }
    [[nodiscard]] int size() const { return n; }

    static void set_conv(vm (*CONV_)(const vm&, const vm&)) {
        // verify : https://atcoder.jp/contests/tdpc/tasks/tdpc_fibonacci

        CONV = CONV_;
    }

    // 加算
    MFPS& operator+=(const MFPS& g) {
        if (n >= g.n)
            rep(i, g.n) c[i] += g.c[i];
        else {
            rep(i, n) c[i] += g.c[i];
            repi(i, n, g.n - 1) c.push_back(g.c[i]);
            n = g.n;
        }
        return *this;
    }
    [[nodiscard]] MFPS operator+(const MFPS& g) const { return MFPS(*this) += g; }

    // 定数加算
    MFPS& operator+=(const mint& sc) {
        if (n == 0) {
            n = 1;
            c = {sc};
        } else {
            c[0] += sc;
        }
        return *this;
    }
    [[nodiscard]] MFPS operator+(const mint& sc) const { return MFPS(*this) += sc; }
    [[nodiscard]] friend MFPS operator+(const mint& sc, const MFPS& f) { return f + sc; }
    MFPS& operator+=(const int& sc) {
        *this += mint(sc);
        return *this;
    }
    [[nodiscard]] MFPS operator+(const int& sc) const { return MFPS(*this) += sc; }
    [[nodiscard]] friend MFPS operator+(const int& sc, const MFPS& f) { return f + sc; }

    // 減算
    MFPS& operator-=(const MFPS& g) {
        if (n >= g.n)
            rep(i, g.n) c[i] -= g.c[i];
        else {
            rep(i, n) c[i] -= g.c[i];
            repi(i, n, g.n - 1) c.push_back(-g.c[i]);
            n = g.n;
        }
        return *this;
    }
    [[nodiscard]] MFPS operator-(const MFPS& g) const { return MFPS(*this) -= g; }

    // 定数減算
    MFPS& operator-=(const mint& sc) {
        *this += -sc;
        return *this;
    }
    [[nodiscard]] MFPS operator-(const mint& sc) const { return MFPS(*this) -= sc; }
    [[nodiscard]] friend MFPS operator-(const mint& sc, const MFPS& f) { return -(f - sc); }
    MFPS& operator-=(const int& sc) {
        *this += -sc;
        return *this;
    }
    [[nodiscard]] MFPS operator-(const int& sc) const { return MFPS(*this) -= sc; }
    [[nodiscard]] friend MFPS operator-(const int& sc, const MFPS& f) { return -(f - sc); }

    // 加法逆元
    [[nodiscard]] MFPS operator-() const { return MFPS(*this) *= -1; }

    // 定数倍
    MFPS& operator*=(const mint& sc) {
        rep(i, n) c[i] *= sc;
        return *this;
    }
    [[nodiscard]] MFPS operator*(const mint& sc) const { return MFPS(*this) *= sc; }
    [[nodiscard]] friend MFPS operator*(const mint& sc, const MFPS& f) { return f * sc; }
    MFPS& operator*=(const int& sc) {
        *this *= mint(sc);
        return *this;
    }
    [[nodiscard]] MFPS operator*(const int& sc) const { return MFPS(*this) *= sc; }
    [[nodiscard]] friend MFPS operator*(const int& sc, const MFPS& f) { return f * sc; }

    // 右からの定数除算
    MFPS& operator/=(const mint& sc) {
        *this *= sc.inv();
        return *this;
    }
    [[nodiscard]] MFPS operator/(const mint& sc) const { return MFPS(*this) /= sc; }
    MFPS& operator/=(const int& sc) {
        *this /= mint(sc);
        return *this;
    }
    [[nodiscard]] MFPS operator/(const int& sc) const { return MFPS(*this) /= sc; }

    // 積
    MFPS& operator*=(const MFPS& g) {
        c = CONV(c, g.c);
        n = sz(c);
        return *this;
    }
    [[nodiscard]] MFPS operator*(const MFPS& g) const { return MFPS(*this) *= g; }

    // 除算
    [[nodiscard]] MFPS inv(int d) const {
        // 参考：https://nyaannyaan.github.io/library/fps/formal-power-series.hpp
        // verify : https://judge.yosupo.jp/problem/inv_of_formal_power_series

        // 【方法】
        //  1 / f mod z^d を求めることは，
        //		f g = 1 (mod z^d)
        //  なる g を求めることである．
        //  この d の部分を 1, 2, 4, ..., 2^i と倍々にして求めていく．
        //
        //  d = 1 のときについては
        //		g = 1 / f[0] (mod z^1)
        //  である．
        //
        //  次に，
        //		g = h (mod z^k)
        //  が求まっているとして
        //		g mod z^(2 k)
        //  を求める．最初の式を変形していくことで
        //		g - h = 0 (mod z^k)
        //		⇒ (g - h)^2 = 0 (mod z^(2 k))
        //		⇔ g^2 - 2 g h + h^2 = 0 (mod z^(2 k))
        //		⇒ f g^2 - 2 f g h + f h^2 = 0 (mod z^(2 k))
        //		⇔ g - 2 h + f h^2 = 0 (mod z^(2 k)) 　(f g = 1 (mod z^d) より)
        //		⇔ g = (2 - f h) h (mod z^(2 k))
        //  を得る．
        //
        //  この手順を d ≦ 2^i となる i まで繰り返し，d 次以上の項を削除すればよい．

        Assert(!c.empty());
        Assert(c[0] != 0);

        MFPS g(c[0].inv());
        for (int k = 1; k < d; k <<= 1) {
            int len = max(min(2 * k, d), 1);
            MFPS tmp(0, len);
            rep(i, min(len, n)) tmp[i] = -c[i];  // -f
            tmp *= g;  // -f h
            tmp.resize(len);
            tmp[0] += 2;  // 2 - f h
            g *= tmp;  // (2 - f h) h
            g.resize(len);
        }

        return g;
    }
    MFPS& operator/=(const MFPS& g) { return *this *= g.inv(max(n, g.n)); }
    [[nodiscard]] MFPS operator/(const MFPS& g) const { return MFPS(*this) /= g; }

    // 余り付き除算
    [[nodiscard]] MFPS quotient(const MFPS& g) const {
        // 参考 : https://nyaannyaan.github.io/library/fps/formal-power-series.hpp
        // verify : https://judge.yosupo.jp/problem/division_of_polynomials

        // 【方法】
        //  f(x) = g(x) q(x) + r(x) となる q(x) を求める．
        //  f の次数は n-1, g の次数は m-1 とする．(n ≧ m)
        //  従って q の次数は n-m，r の次数は m-2 となる．
        //
        //  f^R で f の係数列を逆順にした多項式を表す．すなわち
        //		f^R(x) := f(1/x) x^(n-1)
        //  である．他の多項式も同様とする．
        //
        //  最初の式で x → 1/x と置き換えると，
        //		f(1/x) = g(1/x) q(1/x) + r(1/x)
        //		⇔ f(1/x) x^(n-1) = g(1/x) q(1/x) x^(n-1) + r(1/x) x^(n-1)
        //		⇔ f(1/x) x^(n-1) = g(1/x) x^(m-1) q(1/x) x^(n-m) + r(1/x) x^(m-2) x^(n-m+1)
        //		⇔ f^R(x) = g^R(x) q^R(x) + r^R(x) x^(n-m+1)
        //		⇒ f^R(x) = g^R(x) q^R(x) (mod x^(n-m+1))
        //  	    ⇒ q^R(x) = f^R(x) / g^R(x)  (mod x^(n-m+1))
        //  を得る．
        //
        //  これで q を mod x^(n-m+1) で正しく求めることができることになるが，
        //  q の次数は n-m であったから，q 自身を正しく求めることができた．

        if (n < g.n) return MFPS();
        return ((this->rev() / g.rev()).resize(n - g.n + 1)).rev();
    }
    [[nodiscard]] MFPS reminder(const MFPS& g) const {
        // verify : https://judge.yosupo.jp/problem/division_of_polynomials

        return (*this - this->quotient(g) * g).resize();
    }
    [[nodiscard]] pair<MFPS, MFPS> quotient_remainder(const MFPS& g) const {
        // verify : https://judge.yosupo.jp/problem/division_of_polynomials

        pair<MFPS, MFPS> res;
        res.first = this->quotient(g);
        res.second = (*this - res.first * g).resize();
        return res;
    }

    // スパース積
    MFPS& operator*=(const SMFPS& g) {
        // g の定数項だけ例外処理
        auto it0 = g.begin();
        mint g0 = 0;
        if (it0->first == 0) {
            g0 = it0->second;
            it0++;
        }

        // 後ろからインライン配る DP
        repir(i, n - 1, 0) {
            // 上位項に係数倍して配っていく．
            for (auto it = it0; it != g.end(); it++) {
                auto [j, gj] = *it;

                if (i + j >= n) break;

                c[i + j] += c[i] * gj;
            }

            // 定数項は最後に配るか消去しないといけない．
            c[i] *= g0;
        }

        return *this;
    }
    [[nodiscard]] MFPS operator*(const SMFPS& g) const { return MFPS(*this) *= g; }

    // スパース商
    MFPS& operator/=(const SMFPS& g) {
        // g の定数項だけ例外処理
        auto it0 = g.begin();
        Assert(it0->first == 0 && it0->second != 0);
        mint g0_inv = it0->second.inv();
        it0++;

        // 前からインライン配る DP（後ろに累積効果あり）
        rep(i, n) {
            // 定数項は最初に配らないといけない．
            c[i] *= g0_inv;

            // 上位項に係数倍して配っていく．
            for (auto it = it0; it != g.end(); it++) {
                auto [j, gj] = *it;

                if (i + j >= n) break;

                c[i + j] -= c[i] * gj;
            }
        }

        return *this;
    }
    [[nodiscard]] MFPS operator/(const SMFPS& g) const { return MFPS(*this) /= g; }

    // 係数反転
    [[nodiscard]] MFPS rev() const {
        MFPS h = *this;
        reverse(all(h.c));
        return h;
    }

    // 単項式
    [[nodiscard]] static MFPS monomial(int d, mint coef = 1) {
        MFPS mono(0, d + 1);
        mono[d] = coef;
        return mono;
    }

    // 不要な高次項の除去
    MFPS& resize() {
        // 最高次の係数が非 0 になるまで削る．
        while (n > 0 && c[n - 1] == 0) {
            c.pop_back();
            n--;
        }
        return *this;
    }

    // x^d 以上の項を除去する．
    MFPS& resize(int d) {
        n = d;
        c.resize(d);
        return *this;
    }

    // 不定元への代入
    [[nodiscard]] mint assign(const mint& x) const {
        mint val = 0;
        repir(i, n - 1, 0) val = val * x + c[i];
        return val;
    }

    // 係数のシフト
    MFPS& operator>>=(int d) {
        n += d;
        c.insert(c.begin(), d, 0);
        return *this;
    }
    MFPS& operator<<=(int d) {
        n -= d;
        if (n <= 0) {
            c.clear();
            n = 0;
        } else
            c.erase(c.begin(), c.begin() + d);
        return *this;
    }
    [[nodiscard]] MFPS operator>>(int d) const { return MFPS(*this) >>= d; }
    [[nodiscard]] MFPS operator<<(int d) const { return MFPS(*this) <<= d; }

#ifdef _MSC_VER
    friend ostream& operator<<(ostream& os, const MFPS& f) {
        if (f.n == 0)
            os << 0;
        else {
            rep(i, f.n) {
                os << f[i] << "z^" << i;
                if (i < f.n - 1) os << " + ";
            }
        }
        return os;
    }
#endif
};
