template <typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &G, int start = 0) {
    int n = G.size();
    vector<T> dst(n, numeric_limits<T>::max());
    priority_queue<pair<T, int>> pq;
    dst[start] = 0;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        auto [dst_sum, now] = pq.top();
        pq.pop();
        dst_sum = -dst_sum;
        if (dst[now] < dst_sum) continue;
        for (auto [nxt, cost] : G[now]) {
            if (dst[nxt] > dst[now] + cost) {
                dst[nxt] = dst[now] + cost;
                pq.push(make_pair(-dst[nxt], nxt));
            }
        }
    }
    return dst;
}
