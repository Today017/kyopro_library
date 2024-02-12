tuple<long long, long long, long long> extgcd(long long a, long long b) {
    if (b == 0) return make_tuple(a, 1, 0);
    long long q = a / b, r = a % b;
    auto [g, s, t] = extgcd(b, r);
    long long x = t;
    long long y = s - q * t;
    return make_tuple(g, x, y);
}

long long modinv(long long a, long long mod) {
    auto [g, x, y] = extgcd(a, mod);
    if (g != 1) return -1;
    return x % mod;
}