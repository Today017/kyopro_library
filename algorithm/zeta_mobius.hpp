#pragma once
#include"../../kyopro_library/template.hpp"
//#include"../../kyopro_library/others/bit.hpp"

///@brief ゼータ変換・メビウス変換
namespace ZetaMobius {
    ///@brief 高速ゼータ変換（下位集合）
    ///@brief V'[s] = Σ_{t⊆s} V[t] なる V' を返す
    ///@note |V| = 2^N として O(N 2^N)
    template<typename Monoid>
    vector<typename Monoid::Type> SubsetZeta(vector<typename Monoid::Type> V) {
        int N=Bit::TopBit((int)V.size());
        rep(i,N) rep(j,1<<N) {
            if(j>>i&1) V[j]=Monoid::op(V[j],V[j^(1<<i)]);
        }
        return V;
    }

    ///@brief 高速ゼータ変換（上位集合）
    ///@brief V'[s] = Σ_{t⊇s} V[t] なる V' を返す
    ///@note |V| = 2^N として O(N 2^N)
    template<typename Monoid>
    vector<typename Monoid::Type> SupersetZeta(vector<typename Monoid::Type> V) {
        int N=Bit::TopBit((int)V.size());
        rep(i,N) rep(j,1<<N) {
            if(~j>>i&1) V[j]=Monoid::op(V[j],V[j^(1<<i)]);
        }
        return V;
    }

    ///@brief 高速メビウス変換（下位集合）
    ///@brief V[s] = Σ_{t⊆s} V'[t] なる V' を返す
    ///@note 逆変換が必要なので、v は可換群の元である必要がある
    ///@note |V| = 2^N として O(N 2^N)
    template<typename Abel>
    vector<typename Abel::Type> SubsetMobius(vector<typename Abel::Type> V) {
        int N=Bit::TopBit((int)V.size());
        rep(i,N) rep(j,1<<N) {
            if(j>>i&1) V[j]=Abel::op(V[j],Abel::inv(V[j^(1<<i)]));
        }
        return V;
    }

    ///@brief 高速メビウス変換（上位集合）
    ///@brief V[s] = Σ_{t⊇s} V'[t] なる V' を返す
    ///@note 逆変換が必要なので、v は可換群の元である必要がある
    ///@note |V| = 2^N として O(N 2^N)
    template<typename Abel>
    vector<typename Abel::Type> SupersetMobius(vector<typename Abel::Type> V) {
        int N=Bit::TopBit((int)V.size());
        rep(i,N) rep(j,1<<N) {
            if(~j>>i&1) V[j]=Abel::op(V[j],Abel::inv(V[j^(1<<i)]));
        }
        return V;
    }
}

///@brief 畳み込み
namespace ConvolutionBit {
    template<typename Ring>
    vector<typename Ring::Type> OrConvolution(
        vector<typename Ring::Type> A,
        vector<typename Ring::Type> B
    ) {
        using Type=typename Ring::Type;
        int N=max(A.size(),B.size());

        struct Abel {
            using Type=typename Ring::Type;
            static Type op(const Type& l, const Type& r) { return Ring::plus(l,r); }
            static Type inv(const Type& x) { return Ring::inv(x); }
            static Type id() { return Ring::zero(); }
        };

        A=move(ZetaMobius::SubsetZeta<Abel>(A));
        B=move(ZetaMobius::SubsetZeta<Abel>(B));
        rep(i,N) A[i]=Ring::mul(A[i],B[i]);
        A=move(ZetaMobius::SubsetMobius<Abel>(A));

        return A;
    }

    template<typename Ring>
    vector<typename Ring::Type> AndConvolution(
        vector<typename Ring::Type> A,
        vector<typename Ring::Type> B
    ) {
        using Type=typename Ring::Type;
        int N=max(A.size(),B.size());

        struct Abel {
            using Type=typename Ring::Type;
            static Type op(const Type& l, const Type& r) { return Ring::plus(l,r); }
            static Type inv(const Type& x) { return Ring::inv(x); }
            static Type id() { return Ring::zero(); }
        };

        A=move(ZetaMobius::SupersetZeta<Abel>(A));
        B=move(ZetaMobius::SupersetZeta<Abel>(B));
        rep(i,N) A[i]=Ring::mul(A[i],B[i]);
        A=move(ZetaMobius::SupersetMobius<Abel>(A));

        return A;
    }

    template<typename Ring>
    vector<typename Ring::Type> SubsetConvolution(
        vector<typename Ring::Type> A,
        vector<typename Ring::Type> B
    ) {
        using Type=typename Ring::Type;
        int N=max(A.size(),B.size());
        int M=Bit::TopBit(N);

        vector<vector<Type>> A2(M+1,vector<Type>(N)), B2=A2;
        rep(i,N) {
            A2[Bit::PopCount(i)][i]=A[i];
            B2[Bit::PopCount(i)][i]=B[i];
        }

        struct Abel {
            using Type=typename Ring::Type;
            static Type op(const Type& l, const Type& r) { return Ring::plus(l,r); }
            static Type inv(const Type& x) { return Ring::inv(x); }
            static Type id() { return Ring::zero(); }
        };

        rep(i,M+1) {
            A2[i]=move(ZetaMobius::SubsetZeta<Abel>(A2[i]));
            B2[i]=move(ZetaMobius::SubsetZeta<Abel>(B2[i]));
        }

        vector<vector<Type>> conv(M+1,vector<Type>(N));
        for(int i=0; i<=M; i++) for(int j=0; i+j<=M; j++) {
            rep(k,N) conv[i+j][k]=Ring::plus(conv[i+j][k],Ring::mul(A2[i][k],B2[j][k]));
        }

        rep(i,M+1) conv[i]=move(ZetaMobius::SubsetMobius<Abel>(conv[i]));

        rep(i,N) A[i]=conv[Bit::PopCount(i)][i];
        return A;
    }
}

#include"../../kyopro_library/others/monoid.hpp"
#include"../../kyopro_library/others/abel.hpp"
#include"../../kyopro_library/others/ring.hpp"
