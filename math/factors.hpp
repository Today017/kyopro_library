#include"../../kyopro_library/template.hpp"

///@brief エラトステネスの篩を利用した高速な素因数分解・約数列挙
///@ref https://osak.jp/diary/diary_201310.html#20131017
///@ref https://qiita.com/drken/items/3beb679e54266f20ab63 
struct Factors {
    ///@brief 前計算
    ///@note O(n log(log(n)))
    Factors(int n) {
        lpf.assign(n+1,INF);
        divisors.resize(n+1);
        prime_factors.resize(n+1);
        for(int i=2; i<=n; i++) if(lpf[i]==INF) {
            for(int j=i; j<=n; j+=i) chmin(lpf[j],i);
        }
    }

    ///@brief n を素因数分解する
    ///@note O(log(n))
    vector<pair<int,int>>& get_prime_factors(int n) {
        if(prime_factors[n].size()==0) {
            int x=n;
            while(x>1) {
                int p=lpf[x];
                int cnt=0;
                while(x%p==0) {
                    x/=p;
                    cnt++;
                }
                prime_factors[n].push_back({p,cnt});
            }
        }
        return prime_factors[n];
    }

    ///@brief n の約数を返す
    ///@note O(d(n))
    vector<int>& get_divisors(int n) {
        if(divisors[n].size()==0) {
            vector<pair<int,int>> pf=get_prime_factors(n);
            int sz=pf.size();
            auto dfs=[&](auto&& dfs, int i, int x)-> void {
                if(i==sz) {
                    divisors[n].push_back(x);
                    return;
                }
                auto[p,cnt]=pf[i];
                for(int j=0; j<=cnt; j++) {
                    dfs(dfs,i+1,x);
                    x*=p;
                }
            };
            dfs(dfs,0,1);
            sort(all(divisors[n]));
        }
        return divisors[n];
    }

private:
    vector<int> lpf;
    vector<vector<int>> divisors;
    vector<vector<pair<int,int>>> prime_factors;
};