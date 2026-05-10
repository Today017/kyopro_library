#include"../../kyopro_library/template.hpp"

///@brief Binary Trie
///@ref verify: https://judge.yosupo.jp/problem/ordered_set
///@ref verify: https://judge.yosupo.jp/problem/set_xor_min
template<int Log=32>
struct BinaryTrie {
    BinaryTrie(): nodes(1), lazy_xor(0), siz(0) {}

    void reserve(int x) { nodes.reserve(x); }

    ///@brief すべての要素vをv xor xで置き換える
    ///@note O(1)
    void apply_xor(ll x) { lazy_xor^=x; }

    ///@brief valをk個追加する
    void insert(ll val, ll k=1) {
        siz+=k;
        int idx=0;
        val^=lazy_xor;
        per(i,Log) {
            int lr=val>>i&1;
            if(nodes[idx].ch[lr]==-1) {
                nodes[idx].ch[lr]=nodes.size();
                nodes.push_back(Node());
            }
            idx=nodes[idx].ch[lr];
            nodes[idx].count+=k;
        }
    }

    ///@brief valをmin(k,count(val)個削除する
    void discard(ll val, ll k=1) {
        chmin(k,count(val));
        siz-=k;
        int idx=0;
        val^=lazy_xor;
        per(i,Log) {
            int lr=val>>i&1;
            if(nodes[idx].ch[lr]==-1 || nodes[nodes[idx].ch[lr]].count==0) return;
            idx=nodes[idx].ch[lr];
            nodes[idx].count-=k;
        }
    }

    ///@brief valの個数を返す
    ll count(ll val) const {
        int idx=0;
        val^=lazy_xor;
        per(i,Log) {
            int lr=val>>i&1;
            if(nodes[idx].ch[lr]==-1 || nodes[nodes[idx].ch[lr]].count==0) return 0;
            idx=nodes[idx].ch[lr];
        }
        return nodes[idx].count;
    }

    ///@brief 0-indexedでk番目に小さい要素を返す
    ll kth_min(ll k) const {
        if(k>=siz) return -1;
        int idx=0;
        ll ret=0;
        per(i,Log) {
            int lr=lazy_xor>>i&1;
            int lch=nodes[idx].ch[lr];
            int lcnt=(lch==-1)? 0: nodes[lch].count;
            if(k<lcnt) idx=lch;
            else {
                k-=lcnt;
                idx=nodes[idx].ch[lr^1];
                ret|=1ll<<i;
            }
        }
        return ret;
    }

    ///@brief valより小さい要素の個数を返す
    int count_lt(ll val) const {
        int idx=0;
        ll ret=0;
        per(i,Log) {
            int lr=(val^lazy_xor)>>i&1;
            int l=lazy_xor>>i&1;
            if(lr) {
                int lch=nodes[idx].ch[l];
                if(lch!=-1) ret+=nodes[lch].count;
            }
            idx=nodes[idx].ch[lr^l];
            if(idx==-1 || nodes[idx].count==0) break;
        }
        return ret;
    }

    ll min() const { return kth_min(0); }
    ll max() const { return kth_min(nodes[0].count-1); }

    ll gt(ll val) const {
        ll cnt=count_lt(val+1);
        return cnt<siz? kth_min(cnt): -1;
    }

    ll ge(ll val) const {
        ll cnt=count_lt(val);
        return cnt<siz? kth_min(cnt): -1;
    }

    ll lt(ll val) const {
        ll cnt=count_lt(val);
        return cnt>0? kth_min(cnt-1): -1;
    }

    ll le(ll val) const {
        ll cnt=count_lt(val+1);
        return cnt>0? kth_min(cnt-1): -1;
    }

    int size() const { return siz; }

private:
    struct Node {
        array<int,2> ch;
        ll count;
        Node(): ch({-1,-1}), count(0) {}
    };

    vector<Node> nodes;
    ll lazy_xor;
    ll siz;
};
