#include"../../kyopro_library/template.hpp"

/// @brief Binary Trie
template<typename T=uint32_t, int Log=32>
struct BinaryTrie{
    BinaryTrie(){ root=nullptr; }

    /// @brief BinaryTrie のサイズを返す
    int size()const{
        if(root==nullptr) return 0;
        return root->size;
    }

    /// @brief x を t 個挿入する
    void insert(T x, int t=1){
        root=insert(root,x,Log-1,t);
    }

    /// @brief x を min(count(x), t) 個削除する
    void erase(T x, int t=1){
        chmin(t,count(x));
        if(t==0) return;
        root=erase(root,x,Log-1,t);
    }

    /// @brief 要素全体に x を xor する
    void apply_xor(T x){
        if(root!=nullptr) root->lazy^=x;
    }

    /// @brief 最大値を返す
    T max(){
        return get_min(root,~0,Log-1);
    }

    /// @brief 最小値を返す
    T min(){
        return get_min(root,0,Log-1);
    }

    /// @brief k(0-indexed) 番目に小さい要素を返す
    T kth_min(int k){
        assert(0<=k&&k<size());
        return get(root,k,Log-1);
    }

    /// @brief x 以上の最小の要素が何番目に小さいかを返す
    int lower_bound(T x){
        return count_lower(root,x,Log-1);
    }

    /// @brief x がいくつ含まれているかを返す
    int count(T x){
        if(root==nullptr)return 0;
        Node*v=root;
        for(int i=Log-1; i>=0; i--){
            evaluate(v,i);
            v=v->next[(x>>i)&1];
            if(v==nullptr)return 0;
        }
        return v->size;
    }

private:
    struct Node{
        Node*next[2];
        int size;
        T lazy;
        Node(){
            size=0;
            lazy=0;
            next[0]=next[1]=nullptr;
        }
    };

    Node*root;

    void evaluate(Node*v, int bit){
        if((v->lazy>>bit)&1) swap(v->next[0],v->next[1]);
        if(v->next[0]!=nullptr) v->next[0]->lazy^=v->lazy;
        if(v->next[1]!=nullptr) v->next[1]->lazy^=v->lazy;
        v->lazy=0;
    }

    Node*insert(Node*v, T x, int bit, int cnt){
        if(v==nullptr) v=new Node;
        v->size+=cnt;
        if(bit<0) return v;
        evaluate(v,bit);
        int lr=(x>>bit)&1;
        v->next[lr]=insert(v->next[lr],x,bit-1,cnt);
        return v;
    }

    Node*erase(Node*v, T x, int bit, int cnt){
        assert(v!=nullptr);
        v->size-=cnt;
        if(v->size==0) return nullptr;
        if(bit<0) return v;
        evaluate(v,bit);
        int lr=(x>>bit)&1;
        v->next[lr]=erase(v->next[lr],x,bit-1,cnt);
        return v;
    }

    T get_min(Node*v, T x, int bit){
        if(bit<0) return 0;
        evaluate(v,bit);
        int lr=(x>>bit)&1;
        if(v->next[lr]==nullptr) lr=1-lr;
        return get_min(v->next[lr],x,bit-1)|((T)lr<<bit);
    }

    T get(Node*v, int k, int bit){
        if(bit<0) return 0;
        evaluate(v,bit);
        int m=v->next[0]!=nullptr?v->next[0]->size:0;
        if(k<m) return get(v->next[0],k,bit-1);
        else return get(v->next[1],k-m,bit-1)|((T)1<<bit);
    }

    int count_lower(Node*v,T x,int bit){
        if(v==nullptr||bit<0) return 0;
        evaluate(v,bit);
        int lr=(x>>bit)&1;
        int ret=lr&&v->next[0]!=nullptr?v->next[0]->size:0;
        return ret+count_lower(v->next[lr],x,bit-1);
    }
};