///@brief Trie, Aho-Corasick
//https://ei1333.github.io/library/string/aho-corasick.hpp に適宜コメントを付けただけです

///@brief TrieNode
///@tparam char_size アルファベットのサイズ
template <int char_size>
struct TrieNode {
    int nxt[char_size];///<子どものノードのインデクス, ないなら-1
    int exist;///<このノードをprefixとして持つ文字列の個数
    vector<int> accept;///<このノードが終点である文字列の個数

    TrieNode() : exist(0) { memset(nxt, -1, sizeof(nxt)); }
};

///@brief Trie
///@tparam char_size アルファベットのサイズ
///@tparam margin 0にあたる文字
template <int char_size, int margin>
struct Trie {
    using Node = TrieNode<char_size>;

private:
    vector<Node> nodes;
    int root;

public:
    Trie() : root(0) { nodes.push_back(Node()); }

private:
    void update_direct(int node, int id) { nodes[node].accept.push_back(id); }
    void update_child(int node, int child, int id) { ++nodes[node].exist; }
    void add(const string& str, int str_index, int node_index, int id) {
        if (str_index == str.size()) {
            update_direct(node_index, id);
        } else {
            const int c = str[str_index] - margin;
            if (nodes[node_index].nxt[c] == -1) {
                nodes[node_index].nxt[c] = (int)nodes.size();
                nodes.push_back(Node());
            }
            add(str, str_index + 1, nodes[node_index].nxt[c], id);
            update_child(node_index, nodes[node_index].nxt[c], id);
        }
    }
    void add(const string& str, int id) { add(str, 0, 0, id); }

public:
    ///@brief 文字列 str を追加する
    ///@note O(|str|)
    void add(const string& str) { add(str, nodes[0].exist); }

private:
    void query(const string& str, const function<void(int)>& f, int str_index,
            int node_index) {
        for (auto& idx : nodes[node_index].accept) f(idx);
        if (str_index == str.size()) {
            return;
        } else {
            const int c = str[str_index] - margin;
            if (nodes[node_index].nxt[c] == -1) return;
            query(str, f, str_index + 1, nodes[node_index].nxt[c]);
        }
    }

public:
    ///@brief strのprefixと一致する文字列のインデックスそれぞれに対してfを実行する
    ///@note O(|str| + (見つかった文字列の総数)*|f|)
    void query(const string& str, const function<void(int)>& f) {
        query(str, f, 0, 0);
    }

    ///@brief 文字列の総数
    int count() const { return (nodes[0].exist); }

    ///@brief ノードの総数
    int size() const { return ((int)nodes.size()); }
};

///@brief AhoCorasick
template <int char_size, int margin>
struct AhoCorasick : Trie<char_size + 1, margin> {
    using Trie<char_size + 1, margin>::Trie;

private:
    const int FAIL = char_size;
    vector<int> correct;

public:
    ///@brief 前計算 オートマトンを構築する
    ///@note O(文字列の長さの総和)
    void build(bool heavy = true) {
        correct.resize(this->size());
        for (int i = 0; i < this->size(); i++) {
            correct[i] = (int)this->nodes[i].accept.size();
        }
        queue<int> que;
        for (int i = 0; i <= char_size; i++) {
            if (~this->nodes[0].nxt[i]) {
                this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
                que.emplace(this->nodes[0].nxt[i]);
            } else {
                this->nodes[0].nxt[i] = 0;
            }
        }
        while (!que.empty()) {
            auto& now = this->nodes[que.front()];
            int fail = now.nxt[FAIL];
            correct[que.front()] += correct[fail];
            que.pop();
            for (int i = 0; i < char_size; i++) {
                if (~now.nxt[i]) {
                    this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
                    if (heavy) {
                        auto& u = this->nodes[now.nxt[i]].accept;
                        auto& v = this->nodes[this->nodes[fail].nxt[i]].accept;
                        vector<int> accept;
                        set_union(begin(u), end(u), begin(v), end(v),
                                back_inserter(accept));
                        u = accept;
                    }
                    que.emplace(now.nxt[i]);
                } else {
                    now.nxt[i] = this->nodes[fail].nxt[i];
                }
            }
        }
    }

    ///@brief str の中に出現する全パターンの出現回数を返す
    ///@note O(|str|)
    unordered_map<int, int> match(const string& str, int now = 0) {
        unordered_map<int, int> result, visit_cnt;
        for (auto& c : str) {
            now = this->nodes[now].nxt[c - margin];
            visit_cnt[now]++;
        }
        for (auto& [now, cnt] : visit_cnt) {
            for (auto& v : this->nodes[now].accept) result[v] += cnt;
        }
        return result;
    }

    ///@brief 現在のノード now から文字 c で遷移したときの（見つかったパターンの総数, 次のノード）を返す
    ///@note O(1)
    pair<int64_t, int> move(const char& c, int now = 0) {
        now = this->nodes[now].nxt[c - margin];
        return {correct[now], now};
    }

    ///@brief str に対して move を適用する。（見つかったパターンの総数, 最終ノードを返す）
    ///@note O(|str|)
    pair<int64_t, int> move(const string& str, int now = 0) {
        int64_t sum = 0;
        for (auto& c : str) {
            auto nxt = move(c, now);
            sum += nxt.first;
            now = nxt.second;
        }
        return {sum, now};
    }
};
