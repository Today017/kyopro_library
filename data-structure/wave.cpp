enum {
    NOTFOUND = 0xFFFFFFFFFFFFFFFFLLU
};

using ull = uint64_t;
class succinct_bit_vector {
private:
    const ull size;  // ビットベクトルのサイズ
    static const ull blockBitNum = 16;
    static const ull LEVEL_L = 512;
    static const ull LEVEL_S = 16;

    vector<ull> L;  // 大ブロック
    vector<uint16_t> S;  // 小ブロック
    vector<uint16_t> B;  // ビットベクトル

    ull numOne = 0;  // 1bitの数

public:
    explicit succinct_bit_vector(const ull n) : size(n) {
        const ull s = (n + blockBitNum - 1) / blockBitNum + 1;  // ceil(n, blockSize)
        this->B.assign(s, 0);
        this->L.assign(n / LEVEL_L + 1, 0);
        this->S.assign(n / LEVEL_S + 1, 0);
    }

    // B[pos] = bit
    void set_bit(const ull bit, const ull pos) {
        assert(bit == 0 or bit == 1);
        assert(pos < this->size);

        const ull blockPos = pos / blockBitNum;
        const ull offset = pos % blockBitNum;
        if (bit == 1) {
            B.at(blockPos) |= (1LLU << offset);
        } else {
            B.at(blockPos) &= (~(1LLU << offset));
        }
    }

    // B[pos]
    ull access(const ull pos) {
        assert(pos < this->size);
        const ull blockPos = pos / blockBitNum;
        const ull offset = pos % blockBitNum;
        return ((B.at(blockPos) >> offset) & 1);
    }

    void build() {
        ull num = 0;
        for (ull i = 0; i <= size; i++) {
            if (i % LEVEL_L == 0) {
                L.at(i / LEVEL_L) = num;
            }
            if (i % LEVEL_S == 0) {
                S.at(i / LEVEL_S) = num - L.at(i / LEVEL_L);
            }
            if (i != size and i % blockBitNum == 0) {
                num += this->pop_count(this->B.at(i / blockBitNum));
            }
        }
        this->numOne = num;
    }

    // B[0, pos)のbitの数
    ull rank(const ull bit, const ull pos) {
        assert(bit == 0 or bit == 1);
        assert(pos <= this->size);

        if (bit) {
            return L[pos / LEVEL_L] + S[pos / LEVEL_S] + pop_count(B[pos / blockBitNum] & ((1 << (pos % blockBitNum)) - 1));
        } else {
            return pos - rank(1, pos);
        }
    }

    // rank番目のbitの位置 + 1(rankは1-origin)
    ull select(const ull bit, const ull rank) {
        assert(bit == 0 or bit == 1);
        assert(rank > 0);
        if (bit == 0 and rank > this->size - this->numOne) {
            return NOTFOUND;
        }
        if (bit == 1 and rank > this->numOne) {
            return NOTFOUND;
        }

        // 大ブロックL内を検索
        ull large_idx = 0;
        {
            ull left = 0;
            ull right = L.size();
            while (right - left > 1) {
                ull mid = (left + right) / 2;
                ull r = L.at(mid);
                r = (bit) ? r : mid * LEVEL_L - L.at(mid);

                if (r < rank) {
                    left = mid;
                    large_idx = mid;
                } else {
                    right = mid;
                }
            }
        }

        // 小ブロックS内を検索
        ull small_idx = (large_idx * LEVEL_L) / LEVEL_S;
        {
            ull left = (large_idx * LEVEL_L) / LEVEL_S;
            ull right = min(((large_idx + 1) * LEVEL_L) / LEVEL_S, (ull)S.size());
            while (right - left > 1) {
                ull mid = (left + right) / 2;
                ull r = L.at(large_idx) + S.at(mid);
                r = (bit) ? r : mid * LEVEL_S - r;

                if (r < rank) {
                    left = mid;
                    small_idx = mid;
                } else {
                    right = mid;
                }
            }
        }

        // Bをブロック単位で順番に探索
        ull rank_pos = 0;
        {
            const ull begin_block_idx = (small_idx * LEVEL_S) / blockBitNum;
            ull total_bit = L.at(large_idx) + S.at(small_idx);
            if (bit == 0) {
                total_bit = small_idx * LEVEL_S - total_bit;
            }
            for (ull i = 0;; ++i) {
                ull b = pop_count(B.at(begin_block_idx + i));
                if (bit == 0) {
                    b = blockBitNum - b;
                }
                if (total_bit + b >= rank) {
                    ull block = (bit) ? B.at(begin_block_idx + i) : ~B.at(begin_block_idx + i);
                    rank_pos = (begin_block_idx + i) * blockBitNum + select_in_block(block, rank - total_bit);
                    break;
                }
                total_bit += b;
            }
        }

        return rank_pos + 1;
    }

    ull get_num_one() const {
        return numOne;
    }

private:
    ull pop_count(ull x) {
        x = (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);
        x = (x & 0x3333333333333333ULL) + ((x >> 2) & 0x3333333333333333ULL);
        x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
        x = x + (x >> 8);
        x = x + (x >> 16);
        x = x + (x >> 32);
        return x & 0x7FLLU;
    }

    ull select_in_block(ull x, ull rank) {
        ull x1 = x - ((x & 0xAAAAAAAAAAAAAAAALLU) >> 1);
        ull x2 = (x1 & 0x3333333333333333LLU) + ((x1 >> 2) & 0x3333333333333333LLU);
        ull x3 = (x2 + (x2 >> 4)) & 0x0F0F0F0F0F0F0F0FLLU;

        ull pos = 0;
        for (;; pos += 8) {
            ull rank_next = (x3 >> pos) & 0xFFLLU;
            if (rank <= rank_next) break;
            rank -= rank_next;
        }

        ull v2 = (x2 >> pos) & 0xFLLU;
        if (rank > v2) {
            rank -= v2;
            pos += 4;
        }

        ull v1 = (x1 >> pos) & 0x3LLU;
        if (rank > v1) {
            rank -= v1;
            pos += 2;
        }

        ull v0 = (x >> pos) & 0x1LLU;
        if (v0 < rank) {
            rank -= v0;
            pos += 1;
        }

        return pos;
    }
};

class wavelet_matrix {
private:
    vector<succinct_bit_vector> bit_arrays;
    vector<ull> begin_one;  // 各bitに着目したときの1の開始位置
    map<ull, ull> begin_alphabet;  // 最後のソートされた配列で各文字の開始位置
    vector<vector<ull>> cumulative_sum;  // 各bitに着目したときの累積和

    ull size;  // 与えられた配列のサイズ
    ull maximum_element;  // 文字数
    ull bit_size;  // 文字を表すのに必要なbit数

public:
    wavelet_matrix(const vector<ull> &array) {
        assert(array.size() > 0);
        size = array.size();
        maximum_element = *max_element(array.begin(), array.end()) + 1;
        bit_size = get_num_of_bit(maximum_element);
        if (bit_size == 0) {
            bit_size = 1;
        }

        for (ull i = 0; i < bit_size; ++i) {
            succinct_bit_vector sv(size);
            bit_arrays.push_back(sv);
        }
        this->begin_one.resize(bit_size);
        this->cumulative_sum.resize(bit_size + 1, vector<ull>(size + 1, 0));

        for (ull j = 0; j < array.size(); ++j) {
            this->cumulative_sum.at(0).at(j + 1) = this->cumulative_sum.at(0).at(j) + array[j];
        }

        vector<ull> v(array);
        for (ull i = 0; i < bit_size; ++i) {
            vector<ull> temp;
            // 0をtempにいれてく
            for (ull j = 0; j < v.size(); ++j) {
                ull c = v.at(j);
                ull bit = (c >> (bit_size - i - 1)) & 1;  // 　上からi番目のbit
                if (bit == 0) {
                    temp.push_back(c);
                    bit_arrays.at(i).set_bit(0, j);
                }
            }

            this->begin_one.at(i) = temp.size();

            // 1をtempにいれてく
            for (ull j = 0; j < v.size(); ++j) {
                ull c = v.at(j);
                ull bit = (c >> (bit_size - i - 1)) & 1;  // 　上からi番目のbit
                if (bit == 1) {
                    temp.push_back(c);
                    bit_arrays.at(i).set_bit(1, j);
                }
            }

            for (ull j = 0; j < temp.size(); ++j) {
                this->cumulative_sum.at(i + 1).at(j + 1) = this->cumulative_sum.at(i + 1).at(j) + temp.at(j);
            }

            bit_arrays.at(i).build();
            v = temp;
        }

        // ソートされた配列内での各文字の位置を取得
        for (int i = v.size() - 1; i >= 0; --i) {
            this->begin_alphabet[v.at(i)] = i;
        }
    }

    // v[pos]
    ull access(ull pos) {
        if (pos >= this->size) {
            return NOTFOUND;
        }

        ull c = 0;
        for (ull i = 0; i < bit_arrays.size(); ++i) {
            ull bit = bit_arrays.at(i).access(pos);  // もとの数値のi番目のbit
            c = (c <<= 1) | bit;
            pos = bit_arrays.at(i).rank(bit, pos);
            if (bit) {
                pos += this->begin_one.at(i);
            }
        }
        return c;
    }

    // i番目のcの位置 + 1を返す。rankは1-origin
    ull select(ull c, ull rank) {
        assert(rank > 0);
        if (c >= maximum_element) {
            return NOTFOUND;
        }
        if (this->begin_alphabet.find(c) == this->begin_alphabet.end()) {
            return NOTFOUND;
        }

        ull index = this->begin_alphabet.at(c) + rank;
        for (ull i = 0; i < bit_arrays.size(); ++i) {
            ull bit = ((c >> i) & 1);  // 下からi番目のbit
            if (bit == 1) {
                index -= this->begin_one.at(bit_size - i - 1);
            }
            index = this->bit_arrays.at(bit_size - i - 1).select(bit, index);
        }
        return index;
    }

    // v[begin_pos, end_pos)で最大値のindexを返す
    ull max_range(ull begin_pos, ull end_pos) {
        return quantile_range(begin_pos, end_pos, end_pos - begin_pos - 1);
    }

    // v[begin_pos, end_pos)で最小値のindexを返す
    ull min_range(ull begin_pos, ull end_pos) {
        return quantile_range(begin_pos, end_pos, 0);
    }

    // v[begin_pos, end_pos)でk番目に小さい数値のindexを返す(kは0-origin)
    // つまり小さい順に並べてk番目の値
    ull quantile_range(ull begin_pos, ull end_pos, ull k) {
        if ((end_pos > size || begin_pos >= end_pos) || (k >= end_pos - begin_pos)) {
            return NOTFOUND;
        }

        ull val = 0;
        for (ull i = 0; i < bit_size; ++i) {
            const ull num_of_zero_begin = bit_arrays.at(i).rank(0, begin_pos);
            const ull num_of_zero_end = bit_arrays.at(i).rank(0, end_pos);
            const ull num_of_zero = num_of_zero_end - num_of_zero_begin;  // beginからendまでにある0の数
            const ull bit = (k < num_of_zero) ? 0 : 1;  // k番目の値の上からi番目のbitが0か1か

            if (bit) {
                k -= num_of_zero;
                begin_pos = this->begin_one.at(i) + begin_pos - num_of_zero_begin;
                end_pos = this->begin_one.at(i) + end_pos - num_of_zero_end;
            } else {
                begin_pos = num_of_zero_begin;
                end_pos = num_of_zero_begin + num_of_zero;
            }

            val = ((val << 1) | bit);
        }

        ull left = 0;
        for (ull i = 0; i < bit_size; ++i) {
            const ull bit = (val >> (bit_size - i - 1)) & 1;  // 上からi番目のbit
            left = bit_arrays.at(i).rank(bit, left);  // cのi番目のbitと同じ数値の数
            if (bit) {
                left += this->begin_one.at(i);
            }
        }

        const ull rank = begin_pos + k - left + 1;
        return select(val, rank) - 1;
    }

    // v[0, pos)のcの数
    ull rank(ull c, ull pos) {
        assert(pos < size);
        if (c >= maximum_element) {
            return 0;
        }
        if (this->begin_alphabet.find(c) == this->begin_alphabet.end()) {
            return 0;
        }

        for (ull i = 0; i < bit_size; ++i) {
            ull bit = (c >> (bit_size - i - 1)) & 1;  // 上からi番目のbit
            pos = bit_arrays.at(i).rank(bit, pos);  // cのi番目のbitと同じ数値の数
            if (bit) {
                pos += this->begin_one.at(i);
            }
        }

        ull begin_pos = this->begin_alphabet.at(c);
        return pos - begin_pos;
    }

    // v[begin_pos, end_pos)で[min, max)に入る値の個数
    ull range_freq(ull begin_pos, ull end_pos, ull min_c, ull max_c) {
        if ((end_pos > size || begin_pos >= end_pos) || (min_c >= max_c) || min_c >= maximum_element) {
            return 0;
        }

        const auto maxi_t = rank_all(max_c, begin_pos, end_pos);
        const auto mini_t = rank_all(min_c, begin_pos, end_pos);
        return get<1>(maxi_t) - get<1>(mini_t);
    }

    // v[0, pos)でcより小さい文字の数
    ull rank_less_than(ull c, ull begin, ull end) {
        auto t = rank_all(c, begin, end);
        return get<1>(t);
    }

    // v[0, pos)でcより大きい文字の数
    ull rank_more_than(ull c, ull begin, ull end) {
        auto t = rank_all(c, begin, end);
        return get<2>(t);
    }

    // v[begin, end)で(cと同じ値の数、cより小さい値の数、cより大きい値の数)を求める
    tuple<ull, ull, ull> rank_all(const ull c, ull begin, ull end) {
        assert(end <= size);
        const ull num = end - begin;

        if (begin >= end) {
            return make_tuple(0, 0, 0);
        }
        if (c >= maximum_element || end == 0) {
            return make_tuple(0, num, 0);
        }

        ull rank_less_than = 0, rank_more_than = 0;
        for (size_t i = 0; i < bit_size && begin < end; ++i) {
            const ull bit = (c >> (bit_size - i - 1)) & 1;

            const ull rank0_begin = this->bit_arrays.at(i).rank(0, begin);
            const ull rank0_end = this->bit_arrays.at(i).rank(0, end);
            const ull rank1_begin = begin - rank0_begin;
            const ull rank1_end = end - rank0_end;

            if (bit) {
                rank_less_than += (rank0_end - rank0_begin);  // i番目のbitが0のものは除外される
                begin = this->begin_one.at(i) + rank1_begin;
                end = this->begin_one.at(i) + rank1_end;
            } else {
                rank_more_than += (rank1_end - rank1_begin);  // i番目のbitが1のものは除外される
                begin = rank0_begin;
                end = rank0_end;
            }
        }

        const ull rank = num - rank_less_than - rank_more_than;
        return make_tuple(rank, rank_less_than, rank_more_than);
    }

    // T[s, e)で出現回数が多い順にk個の(値，頻度)を返す
    // 頻度が同じ場合は値が小さいものが優先される
    vector<pair<ull, ull>> topk(ull s, ull e, ull k) {
        assert(s < e);
        vector<pair<ull, ull>> result;

        // (頻度，深さ，値)の順でソート
        auto c = [](const tuple<ull, ull, ull, ull, ull> &l, const tuple<ull, ull, ull, ull, ull> &r) {
            // width
            if (get<0>(l) != get<0>(r)) {
                return get<0>(l) < get<0>(r);
            }
            // depth
            if (get<3>(l) != get<3>(r)) {
                return get<3>(l) > get<3>(r);
            }
            // value
            if (get<4>(l) != get<4>(r)) {
                return get<4>(l) > get<4>(r);
            }
            return true;
        };

        priority_queue<tuple<ull, ull, ull, ull, ull>, vector<tuple<ull, ull, ull, ull, ull>>, decltype(c)> que(c);  // width, left, right, depth, value
        que.push(make_tuple(e - s, s, e, 0, 0));

        while (not que.empty()) {
            auto element = que.top();
            que.pop();
            ull width, left, right, depth, value;
            tie(width, left, right, depth, value) = element;

            if (depth >= this->bit_size) {
                result.emplace_back(make_pair(value, right - left));
                if (result.size() >= k) {
                    break;
                }
                continue;
            }

            // 0
            const ull left0 = this->bit_arrays.at(depth).rank(0, left);
            const ull right0 = this->bit_arrays.at(depth).rank(0, right);
            if (left0 < right0) {
                que.push(make_tuple(right0 - left0, left0, right0, depth + 1, value));
            }

            // 1
            const ull left1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, left);
            const ull right1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, right);
            if (left1 < right1) {
                que.push(make_tuple(right1 - left1, left1, right1, depth + 1, value | (1 << (bit_size - depth - 1))));
            }
        }

        return result;
    };

    // T[begin_pos, end_pos)でx <= c < yを満たすcの和を返す
    ull range_sum(const ull begin, const ull end, const ull x, const ull y) {
        return range_sum(begin, end, 0, 0, x, y);
    }

    // T[begin_pos, end_pos)でx <= c < yを満たす最大のcを返す
    ull prev_value(const ull begin_pos, const ull end_pos, const ull x, ull y) {
        assert(end_pos <= size);
        const ull num = end_pos - begin_pos;

        if (x >= y or y == 0) {
            return NOTFOUND;
        }
        if (y > maximum_element) {
            y = maximum_element;
        }

        if (begin_pos >= end_pos) {
            return NOTFOUND;
        }
        if (x >= maximum_element || end_pos == 0) {
            return NOTFOUND;
        }

        y--;  // x <= c <= yにする

        stack<tuple<ull, ull, ull, ull, bool>> s;  // (begin, end, depth, c, tight)
        s.emplace(make_tuple(begin_pos, end_pos, 0, 0, true));

        while (not s.empty()) {
            ull b, e, depth, c;
            bool tight;
            tie(b, e, depth, c, tight) = s.top();
            s.pop();

            if (depth == bit_size) {
                if (c >= x) {
                    return c;
                }
                continue;
            }

            const ull bit = (y >> (bit_size - depth - 1)) & 1;

            const ull rank0_begin = this->bit_arrays.at(depth).rank(0, b);
            const ull rank0_end = this->bit_arrays.at(depth).rank(0, e);
            const ull rank1_begin = b - rank0_begin;
            const ull rank1_end = e - rank0_end;

            // d番目のbitが0のものを使う
            const ull b0 = rank0_begin;
            const ull e0 = rank0_end;
            if (b0 != e0) {  // 範囲がつぶれてない
                const ull c0 = ((c << 1) | 0);
                s.emplace(make_tuple(b0, e0, depth + 1, c0, tight and bit == 0));
            }

            // d番目のbitが1のものを使う
            const ull b1 = this->begin_one.at(depth) + rank1_begin;
            const ull e1 = this->begin_one.at(depth) + rank1_end;
            if (b1 != e1) {
                if (not tight or bit == 1) {
                    const auto c1 = ((c << 1) | 1);
                    s.emplace(make_tuple(b1, e1, depth + 1, c1, tight));
                }
            }
        }

        return NOTFOUND;
    }

    // T[begin_pos, end_pos)でx <= c < yを満たす最小のcを返す
    ull next_value(const ull begin_pos, const ull end_pos, const ull x, const ull y) {
        assert(end_pos <= size);
        const ull num = end_pos - begin_pos;

        if (x >= y or y == 0) {
            return NOTFOUND;
        }

        if (begin_pos >= end_pos) {
            return NOTFOUND;
        }
        if (x >= maximum_element || end_pos == 0) {
            return NOTFOUND;
        }

        stack<tuple<ull, ull, ull, ull, bool>> s;  // (begin, end, depth, c, tight)
        s.emplace(make_tuple(begin_pos, end_pos, 0, 0, true));

        while (not s.empty()) {
            ull b, e, depth, c;
            bool tight;
            tie(b, e, depth, c, tight) = s.top();
            s.pop();

            if (depth == bit_size) {
                if (c < y) {
                    return c;
                }
                continue;
            }

            const ull bit = (x >> (bit_size - depth - 1)) & 1;

            const ull rank0_begin = this->bit_arrays.at(depth).rank(0, b);
            const ull rank0_end = this->bit_arrays.at(depth).rank(0, e);
            const ull rank1_begin = b - rank0_begin;
            const ull rank1_end = e - rank0_end;

            // d番目のbitが1のものを使う
            const ull b1 = this->begin_one.at(depth) + rank1_begin;
            const ull e1 = this->begin_one.at(depth) + rank1_end;
            if (b1 != e1) {
                const auto c1 = ((c << 1) | 1);
                s.emplace(make_tuple(b1, e1, depth + 1, c1, tight and bit == 1));
            }

            // d番目のbitが0のものを使う
            const ull b0 = rank0_begin;
            const ull e0 = rank0_end;
            if (b0 != e0) {
                if (not tight or bit == 0) {
                    const ull c0 = ((c << 1) | 0);
                    s.emplace(make_tuple(b0, e0, depth + 1, c0, tight));
                }
            }
        }

        return NOTFOUND;
    }

    // T[s1, e1)とT[s2, e2)に共通して出現する要素を求める
    vector<tuple<ull, ull, ull>> intersect(ull _s1, ull _e1, ull _s2, ull _e2) {
        assert(_s1 < _e1);
        assert(_s2 < _e2);

        vector<tuple<ull, ull, ull>> intersection;

        queue<tuple<ull, ull, ull, ull, ull, ull>> que;  // s1, e1, s2, e2, depth, value
        que.push(make_tuple(_s1, _e1, _s2, _e2, 0, 0));
        while (not que.empty()) {
            auto e = que.front();
            que.pop();
            ull s1, e1, s2, e2, depth, value;
            tie(s1, e1, s2, e2, depth, value) = e;

            if (depth >= this->bit_size) {
                intersection.emplace_back(make_tuple(value, e1 - s1, e2 - s2));
                continue;
            }

            // 0
            ull s1_0 = this->bit_arrays.at(depth).rank(0, s1);
            ull e1_0 = this->bit_arrays.at(depth).rank(0, e1);
            ull s2_0 = this->bit_arrays.at(depth).rank(0, s2);
            ull e2_0 = this->bit_arrays.at(depth).rank(0, e2);

            if (s1_0 != e1_0 and s2_0 != e2_0) {
                que.push(make_tuple(s1_0, e1_0, s2_0, e2_0, depth + 1, value));
            }

            // 1
            ull s1_1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, s1);
            ull e1_1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, e1);
            ull s2_1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, s2);
            ull e2_1 = this->begin_one.at(depth) + this->bit_arrays.at(depth).rank(1, e2);

            if (s1_1 != e1_1 and s2_1 != e2_1) {
                que.push(make_tuple(s1_1, e1_1, s2_1, e2_1, depth + 1, value | (1 << bit_size - depth - 1)));
            }
        }

        return intersection;
    };

private:
    ull get_num_of_bit(ull x) {
        if (x == 0) return 0;
        x--;
        ull bit_num = 0;
        while (x >> bit_num) {
            ++bit_num;
        }
        return bit_num;
    }

    ull range_sum(const ull begin, const ull end, const ull depth, const ull c, const ull x, const ull y) {
        if (begin == end) {
            return 0;
        }

        if (depth == bit_size) {
            if (x <= c and c < y) {
                return c * (end - begin);  // 値 * 頻度
            }
            return 0;
        }

        const ull next_c = ((ull)1 << (bit_size - depth - 1)) | c;  // 上からdepth番目のbitを立てる
        const ull all_one_c = (((ull)1 << (bit_size - depth - 1)) - 1) | next_c;  // depth以降のbitをたてる(これ以降全部1を選んだときの値)
        if (all_one_c < x or y <= c) {
            return 0;
        }

        // [begin, pos)のすべての要素は[x, y)
        if (x <= c and all_one_c < y) {
            return this->cumulative_sum.at(depth).at(end) - this->cumulative_sum.at(depth).at(begin);
        }

        const ull rank0_begin = this->bit_arrays.at(depth).rank(0, begin);
        const ull rank0_end = this->bit_arrays.at(depth).rank(0, end);
        const ull rank1_begin = begin - rank0_begin;
        const ull rank1_end = end - rank0_end;

        return range_sum(rank0_begin, rank0_end, depth + 1, c, x, y) +
               range_sum(this->begin_one.at(depth) + rank1_begin, this->begin_one[depth] + rank1_end, depth + 1, next_c, x, y);
    }
};
