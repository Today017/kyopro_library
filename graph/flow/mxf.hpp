#include "../../../kyopro_library/template.hpp"

struct MXF{
    struct Edge{
        int to,rev;
        ll cap;
        Edge(int to,ll cap,int rev){this->to=to;this->cap=cap;this->rev=rev;}
    };

    vector<Edge> es;
    vector<vector<Edge>> graph;
    vector<int> level,iter;

    MXF(int n){graph.resize(n),level.resize(n),iter.resize(n);}

    void add_edge(int from,int to,ll cap){
        graph[from].push_back(Edge(to,cap,graph[to].size()));
        graph[to].push_back(Edge(from,0,(int)graph[from].size()-1));
        es.push_back(Edge(to,cap,graph[to].size()-1));
    }

    void bfs(int s){
        fill(level.begin(),level.end(),-1);
        queue<int> q;
        level[s]=0;
        q.push(s);
        while(!q.empty()){
            int now=q.front();
            q.pop();
            for(auto[to,rev,cap]:graph[now]){
                if(cap>0&&level[to]<0){
                    level[to]=level[now]+1;
                    q.push(to);
                }
            }
        }
    }

    ll dfs(int now,int t,ll f){
        if(now==t) return f;
        for(int &i=iter[now];i<(int)graph[now].size();i++){
            auto[to,rev,cap]=graph[now][i];
            if(cap>0&&level[now]<level[to]){
                ll d=dfs(to,t,min(f,cap));
                if(d>0){
                    graph[now][i].cap-=d;
                    graph[to][rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }

    // s から t への最大流を求める O(V^2E)
    ll flow(int s,int t){
        ll ret=0;
        while(true){
            bfs(s);
            if(level[t]<0) return ret;
            fill(iter.begin(),iter.end(),0);
            ll f;
            while((f=dfs(s,t,INFL))>0) ret+=f;
        }
    }

    vector<Edge> edges(){return es;}
};