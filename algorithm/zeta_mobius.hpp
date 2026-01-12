#include"../../kyopro_library/template.hpp"

///@brief ゼータ変換・メビウス変換
namespace ZetaMobius {
    ///@brief 高速ゼータ変換（下位集合）
    ///@brief v'[s] = Σ_{t⊆s} v[t] なる v' を返す
    ///@note |v| = 2^N として O(N 2^N)
    template<typename Monoid>
    vector<typename Monoid::Type> SubsetZeta(vector<typename Monoid::Type> v) {
        int n=__lg(v.size());
        rep(i,n) rep(j,1<<n) {
            if(j>>i&1) v[j]=Monoid::op(v[j],v[j^(1<<i)]);
        }
        return v;
    }

    ///@brief 高速ゼータ変換（上位集合）
    ///@brief v'[s] = Σ_{t⊇s} v[t] なる v' を返す
    ///@note |v| = 2^N として O(N 2^N)
    template<typename Monoid>
    vector<typename Monoid::Type> SupersetZeta(vector<typename Monoid::Type> v) {
        int n=__lg(v.size());
        rep(i,n) rep(j,1<<n) {
            if(~j>>i&1) v[j]=Monoid::op(v[j],v[j^(1<<i)]);
        }
        return v;
    }

    ///@brief 高速メビウス変換（下位集合）
    ///@brief v[s] = Σ_{t⊆s} v'[t] なる v' を返す
    ///@note 逆変換が必要なので、v は可換群の元である必要がある
    ///@note |v| = 2^N として O(N 2^N)
    template<typename Abel>
    vector<typename Abel::Type> SubsetMobius(vector<typename Abel::Type> v) {
        int n=__lg(v.size());
        rep(i,n) rep(j,1<<n) {
            if(j>>i&1) v[j]=Abel::op(v[j],Abel::inv(v[j^(1<<i)]));
        }
        return v;
    }

    ///@brief 高速メビウス変換（上位集合）
    ///@brief v[s] = Σ_{t⊇s} v'[t] なる v' を返す
    ///@note 逆変換が必要なので、v は可換群の元である必要がある
    ///@note |v| = 2^N として O(N 2^N)
    template<typename Abel>
    vector<typename Abel::Type> SupersetMobius(vector<typename Abel::Type> v) {
        int n=__lg(v.size());
        rep(i,n) rep(j,1<<n) {
            if(~j>>i&1) v[j]=Abel::op(v[j],Abel::inv(v[j^(1<<i)]));
        }
        return v;
    }
}

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/abel.hpp"