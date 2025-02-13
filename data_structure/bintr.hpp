#include"../../kyopro_library/template.hpp"

template<typename T=uint32_t,int Log=32>
struct BinaryTrie{
	BinaryTrie(){root=nullptr;}
	int size()const{
		if(root==nullptr)return 0;
		return root->size;
	}
	void insert(T x,int cnt=1){root=insert(root,x,Log-1,cnt);}
	void erase(T x,int cnt=1){
		cnt=min(cnt,count(x));
		if(cnt==0)return;
		root=erase(root,x,Log-1,cnt);
	}
	void apply_xor(T x){
		if(root!=nullptr)root->lazy^=x;
	}
	T max_element(T bias=0){return get_min(root,~bias,Log-1);}
	T min_element(T bias=0){return get_min(root,bias,Log-1);}
	T kth_element(int k){
		assert(0<=k&&k<size());
		return get(root,k,Log-1);
	}
	int lower_bound(T x){return count_lower(root,x,Log-1);}
	int upper_bound(T x){return count_lower(root,x+1,Log-1);}
	int count(T x){
		if(root==nullptr)return 0;
		Node*v=root;
		for(int i=Log-1;i>=0;i--){
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
	void evaluate(Node*v,int bit){
		if((v->lazy>>bit)&1)swap(v->next[0],v->next[1]);
		if(v->next[0]!=nullptr)v->next[0]->lazy^=v->lazy;
		if(v->next[1]!=nullptr)v->next[1]->lazy^=v->lazy;
		v->lazy=0;
	}
	Node*insert(Node*v,T x,int bit,int cnt){
		if(v==nullptr)v=new Node;
		v->size+=cnt;
		if(bit<0)return v;
		evaluate(v,bit);
		int lr=(x>>bit)&1;
		v->next[lr]=insert(v->next[lr],x,bit-1,cnt);
		return v;
	}
	Node*erase(Node*v,T x,int bit,int cnt){
		assert(v!=nullptr);
		v->size-=cnt;
		if(v->size==0)return nullptr;
		if(bit<0)return v;
		evaluate(v,bit);
		int lr=(x>>bit)&1;
		v->next[lr]=erase(v->next[lr],x,bit-1,cnt);
		return v;
	}
	T get_min(Node*v,T x,int bit){
		if(bit<0)return 0;
		evaluate(v,bit);
		int lr=(x>>bit)&1;
		if(v->next[lr]==nullptr)lr=1-lr;
		return get_min(v->next[lr],x,bit-1)|((T)lr<<bit);
	}
	T get(Node*v,int k,int bit){
		if(bit<0)return 0;
		evaluate(v,bit);
		int m=v->next[0]!=nullptr?v->next[0]->size:0;
		if(k<m){
			return get(v->next[0],k,bit-1);
		}else{
			return get(v->next[1],k-m,bit-1)|((T)1<<bit);
		}
	}
	int count_lower(Node*v,T x,int bit){
		if(v==nullptr||bit<0)return 0;
		evaluate(v,bit);
		int lr=(x>>bit)&1;
		int ret=lr&&v->next[0]!=nullptr?v->next[0]->size:0;
		return ret+count_lower(v->next[lr],x,bit-1);
	}
};

/*
template<typename T,int L=40>
struct BinaryTrie{
    struct Node{
        array<int,2>ch;
        int cnt;
        Node(){ch.fill(-1),cnt=0;}
    };
    vector<Node>nodes;

    BinaryTrie(){nodes.push_back(Node());}

    void insert(T x){
        int now=0;
        nodes[now].cnt++;
        for(int i=L-1;i>=0;i--){
            int bit=(x>>i)&1;
            if(nodes[now].ch[bit]==-1){
                nodes[now].ch[bit]=nodes.size();
                nodes.push_back(Node());
            }
            now=nodes[now].ch[bit];
            nodes[now].cnt++;
        }
    }

    void erase(T x){
        int now=0;
        nodes[now].cnt--;
        for(int i=L-1;i>=0;i--){
            int bit=(x>>i)&1;
            now=nodes[now].ch[bit];
            nodes[now].cnt--;
        }
    }

    int count(T x){
        int now=0;
        for(int i=L-1;i>=0;i--){
            int bit=(x>>i)&1;
            if(nodes[now].ch[bit]==-1)return 0;
            now=nodes[now].ch[bit];
        }
        return nodes[now].cnt;
    }

    int size(){return nodes[0].cnt;}

    int kth(int k){
        if(k<=0||k>size())return -1;

        int now=0;
        T ret=0;
        for(int i=L-1;i>=0;i--){
            if(now==-1)break;
            if(nodes[now].ch[0]==-1){
                now=nodes[now].ch[1];
                ret|=(1LL<<i);
            }else if(nodes[nodes[now].ch[0]].cnt>=k){
                now=nodes[now].ch[0];
            }else{
                k-=nodes[nodes[now].ch[0]].cnt;
                now=nodes[now].ch[1];
                ret|=(1LL<<i);
            }
        }
        return ret;
    }

    int count_lt(T x){
        int now=0,ret=0;
        for(int i=L-1;i>=0;i--){
            if(now==-1)break;
            int bit=(x>>i)&1;

            if(bit){
                if(nodes[now].ch[0]!=-1)ret+=nodes[nodes[now].ch[0]].cnt;
                now=nodes[now].ch[1];
            }else{
                now=nodes[now].ch[0];
            }
        }
        return ret;
    }

    T ge(T x){//lower_bound
        int c=count_lt(x);
        return kth(c+1);
    }

    T gt(T x){return ge(x+1);}

    T le(T x){
        int c=count_lt(x+1);
        return kth(c);
    }

    T lt(T x){return le(x-1);}
};
*/
