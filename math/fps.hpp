#pragma once
#include"../../kyopro_library/template.hpp"

#include"../../kyopro_library/math/ntt998.hpp"

using Poly=vector<Mod998>; //< 多項式
using PolySparse=vector<pair<int,Mod998>>; //< 疎な多項式（(次数, 係数)の配列）

/// @brief 形式的冪級数
/// @ref https://potato167.github.io/po167_library
namespace FPS {
    /// @brief 多項式 f, g の和を返す
    Poly Add(const Poly& a, const Poly& b) {
        Poly res(max(a.size(),b.size()));
        for(int i=0; i<res.size(); i++) {
            if(i<a.size()) res[i]+=a[i];
            if(i<b.size()) res[i]+=b[i];
        }
        return res;
    }

    /// @brief 多項式 f, g の差を返す
    Poly Sub(const Poly& f, const Poly& g, int len=-1) {
        if(len==-1) len=max(f.size(),g.size());
        Poly res(len);
        for(int i=0; i<len; i++) {
            if(i<f.size()) res[i]+=f[i];
            if(i<g.size()) res[i]-=g[i];
        }
        return res;
    }

    /// @brief 多項式 f, g の積を返す
    Poly Mul(const Poly& f, const Poly& g, int len=-1) {
        auto fg=Convolve998(f,g);
        if(len!=-1) fg.resize(len+1);
        return fg;
    }

    /// @brief 多項式 f に対し、f*g = 1 なる g を返す
    /// @note O(N log(N))
    /// @ref https://judge.yosupo.jp/problem/inv_of_formal_power_series
    Poly Inv(Poly f, int len=-1) {
        /**
         * 方程式 h(g) = 1/g - f = 0 の解を求める問題に変換する
         * ニュートン法より
         *  g_{n+1} = g_n - h(g_n)/h'(g_n)
         * h'(g) = - 1/g^2 より
         *  g_{n+1} = g_n - (1/g_n - f) / (-1/g_n^2)
         *          = g_n + g_n - f*g_n^2
         *          = g_n * (2 - f*g_n)
         * ここで、f*g_n を上位次数の項と下位次数の項 fg_low, fg_high に分けると、
         *  fg_low + fg_high = f*g_n, fg_low = 1 (mod x^d)
         * よって、
         *  g_{n+1} = g_n * (2 - fg_low - fg_high)
         *          = g_n * (1 - fg_high)
         *          = g_n - g_n*fg_high
         */

        if(len==-1) len=f.size();
        assert(f[0]!=0);
        Poly g={f[0].inv()};
        int s=1;
        while(s<len) {
            Poly nxtg(s*2,0), res(s*2,0);
            g.resize(s*2);
            for(int i=0; i<s*2; i++) {
                if(int(f.size())>i) res[i]=f[i];
                nxtg[i]=g[i];
            }

            //fg_high を計算
            NTT998(g); NTT998(res);
            for(int i=0; i<s*2; i++) res[i]*=g[i];
            NTT998(res,true); for(int i=0; i<s; i++) res[i]=0; //fg_high

            //fg_high * g_n を計算
            NTT998(res); for(int i=0; i<s*2; i++) res[i]*=g[i]; NTT998(res,true);

            for(int i=s; i<s*2; i++) nxtg[i]-=res[i];
            swap(nxtg,g);
            s*=2;
        }
        g.resize(len);
        return g;
    }

    /// @brief 多項式 f の積分を返す
    Poly Integral(Poly f) {
        if(f.empty()) return f;
        Poly num_inv((int)f.size()+1);
        num_inv[0]=1; num_inv[1]=1;
        auto m=Mod998::mod();
        for(int i=2; i<=(int)f.size(); i++) num_inv[i]=(-num_inv[m%i])*(Mod998)(m/i);
        f.reserve((int)f.size()+1);
        f.push_back(0);
        for(int i=(int)f.size()-1; i>0; i--) f[i]=f[i-1]*num_inv[i];
        f[0]=0;
        return f;
    }

    /// @brief 多項式 f の微分を返す
    Poly Differential(Poly f) {
        if(f.empty()) return f;
        for(int i=0; i<(int)f.size()-1; i++) f[i]=f[i+1]*(Mod998)(i+1);
        f.pop_back();
        return f;
    }

    /// @brief 多項式 f, g について、`f = gq + r` なる q, r を返す
    pair<Poly,Poly> Div(Poly f, Poly g) {
        int n=f.size(),m=g.size();
        if(n<m) return{{},f};
        Poly r=f;
        reverse(all(f)); reverse(all(g));
        f.resize(n-m+1);
        Poly q=Mul(f,Inv(g,n-m+1));
        q.resize(n-m+1);
        reverse(all(q)); reverse(all(g));
        r=Sub(r,Mul(q,g));
        while(!q.empty()&&q.back()==0) q.pop_back();
        while(!r.empty()&&r.back()==0) r.pop_back();
        return {q,r};
    }

    /// @brief 多項式 f, g の積を返す（ただし、g は疎な多項式として与える）
    Poly MulSparse(Poly f, PolySparse g) {
        auto itr=find_if(g.begin(),g.end(),[&](auto p) { return p.first==0; });
        Mod998 x0=0;
        if(itr!=g.end()) {
            x0=itr->second;
            g.erase(itr);
        }

        for(int i=(int)f.size()-1; i>=0; i--) {
            for(auto& [d,c]: g) {
                if(i+d>=f.size()) continue;
                f[i+d]+=f[i]*c;
            }
            f[i]*=x0;
        }

        return f;
    }

    /// @brief 多項式 f, g に対し、 f / g を返す（ただし、g は疎な多項式として与える）
    Poly DivSparse(Poly f, PolySparse g) {
        auto itr=find_if(g.begin(),g.end(),[&](auto p) { return p.first==0; });
        assert(itr!=g.end());
        Mod998 x0_inv=itr->second.inv();
        g.erase(itr);

        for(int i=0; i<f.size(); i++) {
            f[i]*=x0_inv;
            for(auto& [d,c]: g) {
                if(i+d>=f.size()) continue;
                f[i+d]-=f[i]*c;
            }
        }

        return f;
    }

    namespace Internal {
        const int PRIMITIVE_ROOT=3;

        Poly CyclicConvolution(Poly f, Poly g) {
            NTT998(f); NTT998(g);
            for(int i=0; i<(int)f.size(); i++) f[i]*=g[i];
            NTT998(f,true);
            return f;
        }

        //in :DFT(v)(len(v)=z)
        //out:DFT(v)(len(v)=2*z)
        void Extend(Poly& v) {
            int z=v.size();
            Mod998 e=Mod998(PRIMITIVE_ROOT).pow(Mod998::mod()/(2*z));
            auto cp=v;
            NTT998(cp,true);  rep(i,z) cp[i]*=z;
            Mod998 tmp=Mod998(z).inv();
            for(int i=0; i<z; i++) {
                cp[i]*=tmp;
                tmp*=e;
            }
            NTT998(cp);
            for(int i=0; i<z; i++) v.push_back(cp[i]);
        }

        //s.t|v|=2^s(no assert)
        void PickEvenOdd(Poly& v, int odd) {
            int z=v.size()/2;
            Mod998 half=Mod998(2).inv();
            if(odd==0) {
                for(int i=0; i<z; i++) v[i]=(v[i*2]+v[i*2+1])*half;
                v.resize(z);
            }else{
                Mod998 e=Mod998(PRIMITIVE_ROOT).pow(Mod998::mod()/(2*z));
                Mod998 ie=Mod998(e).inv();
                Poly es={half};
                while((int)es.size()!=z) {
                    Poly n_es((int)es.size()*2);
                    for(int i=0; i<(int)es.size(); i++) {
                        n_es[i*2]=(es[i]);
                        n_es[i*2+1]=(es[i]*ie);
                    }
                    ie*=ie;
                    swap(n_es,es);
                }
                for(int i=0; i<z; i++) v[i]=(v[i*2]-v[i*2+1])*es[i];
                v.resize(z);
            }
        }
    }

    /// @brief 多項式 f について、e^f = Σ[k=0~len-1](f(x)^k/k!) を返す
    Poly Exp(Poly f, int len=-1) {
        /**
         * 方程式 h(g) = log(g) - f = 0 の解を求める問題に変換する。
         * ニュートン法より
         *  g_{n+1} = g_n - h(g_n)/h'(g_n)
         * h(g) = log(g) - f, h'(g) = 1/g  より
         *  g_{n+1} = g_n - (log(g_n) - f) / (1/g_n)
         *          = g_n - g_n(log(g_n) - f)
         *          = g_n * (1 - log(g_n) + f)
         * ここで、log(g_n) を上位項と下位項 lg_low, lg_high に分けると、
         *  log(g_n) = lg_low + lg_high, lg_low = f_low
         * よって、
         *  g_{n+1} = g_n(1 - f_low - lg_high + f)
         *          = g_n(1 + (f - log(g))_high)
         *          = g_n + g_n * (f - log(g))_high
         */

        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{Mod998(1)};
        assert(!f.empty() && f[0]==0);

        int s=1;
        Poly g={Mod998(1)};

        while(s<len) {
            Poly A=g,B=g;
            A=Differential(A); //A = g'
            B=Inv(B,2*s); //B = 1/g
            A.resize(2*s);
            A=Internal::CyclicConvolution(A,B); //A = g'/g
            A.pop_back();
            A=Integral(A); //A = ∫(g'/g)dx = log(g)

            //A = (f-log(g_n))_high
            for(int i=0; i<s; i++) A[i]=0;
            for(int i=s; i<s*2; i++) A[i]=(i<(int)f.size() ? f[i] : 0)-A[i];

            //g_{n+1} = g_n + g_n * (f-log(g))_high
            g.resize(2*s);
            B=Internal::CyclicConvolution(A,g);
            for(int i=s; i<s*2; i++) g[i]=B[i];
            s*=2;
        }
        g.resize(len);
        return g;
    }

    /// @brief 多項式 f について、log(f) を返す
    Poly Log(Poly f, int len=-1) {
        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{Mod998(0)};
        assert(!f.empty()&&f[0]==1);
        Poly res=Convolve998(Differential(f),Inv(f,len));
        res.resize(len-1);
        return Integral(res);
    }

    /// @brief 多項式 f^M を返す
    Poly Pow(Poly f, ll M, int len=-1) {
        if(len==-1) len=f.size();
        Poly res(len,0);
        if(M==0) {
            res[0]=1;
            return res;
        }
        for(int i=0; i<(int)f.size(); i++) {
            if(f[i]==0) continue;
            if(i>(len-1)/M) break;
            Poly g((int)f.size()-i);
            Mod998 v=(Mod998)(1)/(Mod998)(f[i]);
            for(int j=i; j<(int)f.size(); j++) g[j-i]=f[j]*v;
            ll zero=i*M;
            if(i) len-=i*M;
            g=Log(g,len);
            for(Mod998& x:g) x*=M;
            g=Exp(g,len);
            v=(Mod998)(1)/v;
            Mod998 c=1;
            while(M) {
                if(M&1) c=c*v;
                v=v*v;
                M>>=1;
            }
            for(int i=0; i<len; i++) res[i+zero]=g[i]*c;
            return res;
        }
        return res;
    }

    /// @brief `[x^k](P/Q)` を返す
    Mod998 BostanMori(ll k, Poly P, Poly Q) {
        assert(!Q.empty()&&Q[0]!=0);
        int z=1;
        while(z<(int)max(P.size(),Q.size())) z*=2;
        P.resize(z*2,0); Q.resize(z*2,0);
        NTT998(P); NTT998(Q);
        //fast
        while(k) {
            //Q(-x)
            Poly Q_n(z*2);
            for(int i=0; i<z; i++) {
                Q_n[i*2]=Q[i*2+1];
                Q_n[i*2+1]=Q[i*2];
            }
            for(int i=0; i<z*2; i++) {
                P[i]*=Q_n[i];
                Q[i]*=Q_n[i];
            }
            Internal::PickEvenOdd(P,k&1);
            Internal::PickEvenOdd(Q,0);
            k/=2;
            if(k==0) break;
            Internal::Extend(P);
            Internal::Extend(Q);
        }
        Mod998 SP=0,SQ=0;
        for(int i=0; i<z; i++) SP+=P[i],SQ+=Q[i];
        return SP/SQ;
    }

    //0=a[i]*c[0]+a[i-1]*c[1]+a[i-2]*c[2]+...+a[i-d]*c[d]
    //a.size()+1==c.size()
    //c[0]=-1?
    //return a[k]
    Mod998 KthLinear(ll k, Poly a, Poly c) {
        int d=a.size();
        assert(d+1==int(c.size()));
        Poly P=Convolve998(a,c);
        P.resize(d);
        return BostanMori(k,P,c);
    }
}