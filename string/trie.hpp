#include"../../kyopro_library/template.hpp"

struct Trie {
    struct Node{
        array<int,26> to;
        int count_of_end=0,count_of_node=0;
        Node() { fill(ALL(to),-1); }
    };

    Trie(int len) {
        nodes.reserve(len);
        Node root;
        nodes.push_back(root);
    }

    void insert(const string& s) {
        int cur=0;
        for(const char& c:s) {
            int nxt=nodes[cur].to[c-'a'];
            if(nxt==-1) {
                nodes[cur].to[c-'a']=nodes.size();
                nxt=nodes.size();
                nodes.push_back(Node());
            }
            cur=nxt;
            nodes[cur].count_of_node++;
        }
        nodes[cur].count_of_end++;
    }

    int count(const string& s) {
        int cur=0,ret=0;
        for(const char& c:s) {
            int nxt=nodes[cur].to[c-'a'];
            if(nxt==-1) return 0;
            cur=nxt;
            ret=nodes[cur].count_of_end;
        }
    }

    void erase(const string& s) {
        int cur=0;
        for(const char& c:s) {
            int nxt=nodes[cur].to[c-'a'];
            if(nxt==-1) return;
            cur=nxt;
            nodes[cur].count_of_node--;
        }
        nodes[cur].count_of_end--;
    }

private:
    vector<Node> nodes;
};