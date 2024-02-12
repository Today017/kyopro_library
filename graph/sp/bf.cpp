template <typename T>
bool bellman_ford(const vector<tuple<int, int, T>> &edge, int n, int start, vector<T> &dst) {
    dst = vector<T>(n, numeric_limits<T>::max());
    dst[start] = 0;
    int cnt = 0;
    while (cnt < n) {
        bool fin = true;
        for (auto [a, b, c] : edge) {
            if (dst[a] != inf && dst[a] + c < dst[b]) {
                dst[b] = dst[a] + c;
                fin = false;
            }
        }
        if (fin) break;
        cnt++;
    }
    return cnt == n;
}