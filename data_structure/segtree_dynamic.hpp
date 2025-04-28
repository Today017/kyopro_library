#include"../../kyopro_library/template.hpp"

/// @brief 動的セグ木
template<typename Monoid>
struct SegTreeDynamic {
    using Type=typename Monoid::Type;
    struct Node {
        Type value;
        array<int,2> to;
        ll left,right;
        Node(ll l, ll r) {
            to.fill(-1);
            left=l; right=r;
            value=Monoid::id();
        }
    };
    vector<Node> node;

    ll mx=1e9;
    vector<int> route;

    /// @brief サイズ mx の動的セグ木を宣言する
    SegTreeDynamic(ll mx=1e9, int q=5e5) {
        this->mx=mx;
        node.reserve(q);
        node.push_back(Node(0,mx));
        route.reserve(100);
    }

    /// @brief i 番目の要素を v に変える
    void set(ll i, Type v) {
        ll left=0,right=mx,cur=0;
        route.clear();
        while(left<right-1) {
            ll mid=(left+right)/2;

            int nxt,toi;
            if(i<mid) nxt=node[cur].to[0],toi=0; //左
            else nxt=node[cur].to[1],toi=1; //右

            if(nxt==-1) {
                nxt=node.size();
                node[cur].to[toi]=nxt;

                if(toi==0) node.push_back(Node(left,mid));
                else node.push_back(Node(mid,right));
            }

            if(i<mid) right=mid;
            else left=mid;

            route.push_back(cur);
            cur=nxt;
        }
        reverse(ALL(route));
        node[cur].value=v;

        for(int r:route) {
            int leftc=node[r].to[0],rightc=node[r].to[1];
            Type leftv= leftc==-1 ? Monoid::id() : node[leftc].value;
            Type rightv= rightc==-1 ? Monoid::id() : node[rightc].value;
            node[r].value=Monoid::op(leftv,rightv);
        }
    }

    /// @brief 区間 [l, r) のモノイド積を返す
    Type fold(ll l, ll r, int idx=0, ll left=0, ll right=mx) {
        if(right<l||left>r) return Monoid::id();
        if(l<=left&&right<=r) return node[idx].value;

        ll mid=(left+right)/2;
        int leftc=node[idx].to[0],rightc=node[idx].to[1];

        Type leftv,rightv;
        if(leftc==-1) leftv=Monoid::id();
        else leftv=fold(l,r,leftc,left,mid);
        if(rightc==-1) rightv=Monoid::id();
        else rightv=fold(l,r,rightc,mid,right);

        return Monoid::op(leftv,rightv);
    }
};