#include"../../kyopro_library/template.hpp"

/// @brief エラトステネスの篩を利用した高速な素因数分解・約数列挙（Osa_k 法）
/// @ref https://osak.jp/diary/diary_201310.html#20131017
/// @ref https://qiita.com/drken/items/3beb679e54266f20ab63 
struct Factors {
    /// @brief 前計算
    /// @note O(n log(log(n)))
    Factors(int n) {
        mx=n;
        min_factor=VI(mx+1);
        is_prime=VI(mx+1,true); is_prime[0]=is_prime[1]=false;
        divisors=VVI(mx+1);
        prime_factors=vector<vector<pair<int,int>>>(mx+1);
        
        for(int i=2; i<=mx; i++) if(is_prime[i]) {
            min_factor[i]=i;
            for(int j=2*i; j<=mx; j+=i) {
                is_prime[j]=false;
                if(min_factor[j]==0) min_factor[j]=i;
            }
        }
    }

    /// @brief n を素因数分解する
    /// @note O(log(n))
    vector<pair<int,int>> get_prime_factors(int n) {
        if(prime_factors[n].size()==0) {
            int x=n;
            while(x>1) {
                int p=min_factor[x];
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

    /// @brief n の約数を返す
    /// @note O(d(n))
    VI get_divisors(int n) {
        if(divisors[n].size()==0) {
            vector<pair<int,int>> pf=get_prime_factors(n);
            int sz=pf.size();
            auto dfs=[&](auto&& dfs, int i, int x)-> void {
                if(i==sz) {
                    divisors[n].push_back(x);
                    return;
                }
                auto[p,cnt]=pf[i];
                REP(j,cnt+1) {
                    dfs(dfs,i+1,x);
                    x*=p;
                }
            };
            dfs(dfs,0,1);
            sort(ALL(divisors[n]));
        }
        return divisors[n];
    }

private:
    int mx;
    VI min_factor,is_prime;
    VVI divisors;
    vector<vector<pair<int,int>>> prime_factors;
};