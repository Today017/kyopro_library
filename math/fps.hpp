#pragma once
#include"../../kyopro_library/template.hpp"

#include"../../kyopro_library/math/ntt998.hpp"

using Fps=vector<Mod998>; //< 多項式
using FpsSparse=vector<pair<int,Mod998>>; //< 疎な多項式（(次数, 係数)の配列）

/// @brief 形式的冪級数
/// @ref https://potato167.github.io/po167_library
namespace FPS {
    /// @brief 多項式 f, g の和を返す
    Fps Add(const Fps& a, const Fps& b) {
        Fps res(max(a.size(),b.size()));
        for(int i=0; i<res.size(); i++) {
            if(i<a.size()) res[i]+=a[i];
            if(i<b.size()) res[i]+=b[i];
        }
        return res;
    }

    /// @brief 多項式 f, g の差を返す
    Fps Sub(const Fps& a, const Fps& b) {
        Fps res(max(a.size(),b.size()));
        for(int i=0; i<res.size(); i++) {
            if(i<a.size()) res[i]+=a[i];
            if(i<b.size()) res[i]-=b[i];
        }
        return res;
    }

    /// @brief 多項式 f, g の積を返す
    Fps Mul(const Fps& a, const Fps& b) {
        return Convolve998(a,b);
    }

    /// @brief 多項式 f に対し、f*g = 1 なる g を返す
    Fps Inv(Fps f, int len=-1) {
        if(len==-1) len=f.size();
        assert(f[0]!=0);
        Fps g={f[0].inv()};
        int s=1;
        while(s<len) {
            Fps n_g(s*2,0), f_s(s*2,0);
            g.resize(s*2);
            for(int i=0; i<s*2; i++) {
                if(int(f.size())>i) f_s[i]=f[i];
                n_g[i]=g[i];
            }
            NTT998(g); NTT998(f_s);
            for(int i=0; i<s*2; i++) f_s[i]*=g[i];
            NTT998(f_s,true);
            for(int i=0; i<s; i++) f_s[i]=0;
            NTT998(f_s);
            for(int i=0; i<s*2; i++) f_s[i]*=g[i];
            NTT998(f_s,true);
            for(int i=s; i<s*2; i++) n_g[i]-=f_s[i];
            swap(n_g,g);
            s*=2;
        }
        g.resize(len);
        return g;
    }

    /// @brief 多項式 f の積分を返す
    Fps Integral(Fps f) {
        if(f.empty()) return f;
        Fps num_inv((int)f.size()+1);
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
    Fps Differential(Fps f) {
        if(f.empty()) return f;
        for(int i=0; i<(int)f.size()-1; i++) f[i]=f[i+1]*(Mod998)(i+1);
        f.pop_back();
        return f;
    }

    /// @brief 多項式 f について、e^f を返す
    Fps Exp(Fps f, int len=-1) {
        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{Mod998(1)};
        assert(!f.empty()&&f[0]==0);
        int s=1;
        //simple
        Fps g={Mod998(1)};
        while(s<len) {
            //g'/g
            //A*B
            Fps A=g,B=g;
            A=Differential(A);
            B=Inv(B,2*s);
            A.resize(2*s);
            A=Internal::CyclicConvolution(A,B);
            A.pop_back();
            A=Integral(A);
            for(int i=0; i<s; i++) A[i]=0;
            for(int i=s; i<s*2; i++) A[i]=(i<(int)f.size()?f[i]:0)-A[i];
            //g_hat=g(1-g+f)
            //g+=B=g*A
            g.resize(2*s);
            B=Internal::CyclicConvolution(A,g);
            for(int i=s; i<s*2; i++) g[i]=B[i];
            s*=2;
        }
        g.resize(len);
        return g;
    }

    /// @brief 多項式 f について、log(f) を返す
    Fps Log(Fps f, int len=-1) {
        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{Mod998(0)};
        assert(!f.empty()&&f[0]==1);
        Fps res=Convolve998(Differential(f),Inv(f,len));
        res.resize(len-1);
        return Integral(res);
    }

    /// @brief 多項式 f^M を返す
    Fps Pow(Fps f, ll M, int len=-1) {
        if(len==-1) len=f.size();
        Fps res(len,0);
        if(M==0) {
            res[0]=1;
            return res;
        }
        for(int i=0; i<(int)f.size(); i++) {
            if(f[i]==0) continue;
            if(i>(len-1)/M) break;
            Fps g((int)f.size()-i);
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

    /// @brief 多項式 f, g について、`f = gq + r` なる q, r を返す
    pair<Fps,Fps> Div(Fps f, Fps g) {
        int n=f.size(),m=g.size();
        if(n<m) return{{},f};
        Fps r=f;
        reverse(all(f)); reverse(all(g));
        f.resize(n-m+1);
        Fps q=Mul(f,Inv(g,n-m+1));
        q.resize(n-m+1);
        reverse(all(q)); reverse(all(g));
        r=Sub(r,Mul(q,g));
        while(!q.empty()&&q.back()==0) q.pop_back();
        while(!r.empty()&&r.back()==0) r.pop_back();
        return {q,r};
    }

    /// @brief 多項式 f, g の積を返す（ただし、g は疎な多項式として与える）
    Fps MulSparse(Fps f, FpsSparse g) {
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
    Fps DivSparse(Fps f, FpsSparse g) {
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

    /// @brief `[x^k](P/Q)` を返す
    Mod998 BostanMori(ll k, Fps P, Fps Q) {
        assert(!Q.empty()&&Q[0]!=0);
        int z=1;
        while(z<(int)max(P.size(),Q.size())) z*=2;
        P.resize(z*2,0); Q.resize(z*2,0);
        NTT998(P); NTT998(Q);
        //fast
        while(k) {
            //Q(-x)
            Fps Q_n(z*2);
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
    Mod998 KthLinear(ll k, Fps a, Fps c) {
        int d=a.size();
        assert(d+1==int(c.size()));
        Fps P=Convolve998(a,c);
        P.resize(d);
        return BostanMori(k,P,c);
    }

    namespace Internal {
        const int PRIMITIVE_ROOT=3;

        Fps CyclicConvolution(Fps f, Fps g) {
            NTT998(f); NTT998(g);
            for(int i=0; i<(int)f.size(); i++) f[i]*=g[i];
            NTT998(f,true);
            return f;
        }

        //in :DFT(v)(len(v)=z)
        //out:DFT(v)(len(v)=2*z)
        void Extend(Fps& v) {
            int z=v.size();
            Mod998 e=Mod998(PRIMITIVE_ROOT).pow(Mod998::mod()/(2*z));
            auto cp=v;
            NTT998(cp,true);
            Mod998 tmp=1;
            for(int i=0; i<z; i++) {
                cp[i]*=tmp;
                tmp*=e;
            }
            NTT998(cp);
            for(int i=0; i<z; i++) v.push_back(cp[i]);
        }

        //s.t|v|=2^s(no assert)
        void PickEvenOdd(Fps& v, int odd) {
            int z=v.size()/2;
            Mod998 half=(Mod998)(1)/(Mod998)(2);
            if(odd==0) {
                for(int i=0; i<z; i++) v[i]=(v[i*2]+v[i*2+1])*half;
                v.resize(z);
            }else{
                Mod998 e=Mod998(PRIMITIVE_ROOT).pow(Mod998::mod()/(2*z));
                Mod998 ie=Mod998(1)/e;
                Fps es={half};
                while((int)es.size()!=z) {
                    Fps n_es((int)es.size()*2);
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
}