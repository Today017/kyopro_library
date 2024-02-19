struct bezout_identity {
    long long a, b, c, g;
    long long X, Y;
    bezout_identity(long long a, long long b, long long c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    tuple<long long, long long, long long> extgcd(long long a, long long b) {
        if (b == 0) return make_tuple(a, 1, 0);
        long long q = a / b, r = a % b;
        auto [g, s, t] = extgcd(b, r);
        long long x = t;
        long long y = s - q * t;
        return make_tuple(g, x, y);
    }
    bool build() {
        auto [g, X, Y] = extgcd(abs(a), abs(b));
        if (c % g != 0) return false;
        this->g = g;
        this->X = X;
        this->Y = Y;
        if (a < 0) this->X = -this->X;
        if (b < 0) this->Y = -this->Y;
        this->X *= c / g;
        this->Y *= c / g;
        return true;
    }
    pair<long long, long long> general_solution(long long t = 0) {
        long long x = b / g * t + X;
        long long y = -a / g * t + Y;
        return make_pair(x, y);
    }
};
