#include"../../kyopro_library/template.hpp"


#include<atcoder/convolution>
#include<atcoder/modint>

/// @brief 形式的冪級数
/// @ref borrowed from:https://potato167.github.io/po167_library
namespace FPS {
    /// @brief 多項式 f, g の積を返す
    template<typename T>
    vector<T> Mul(const vector<T>& a,const vector<T>& b) {
        return atcoder::convolution(a,b);
    }

    /// @brief 多項式 f, g の和を返す
    template<typename T>
    vector<T> Add(const vector<T>& a, const vector<T>& b) {
        vector<T> res(max(a.size(),b.size()));
        for(int i=0; i<res.size(); i++) {
            if(i<a.size()) res[i]+=a[i];
            if(i<b.size()) res[i]+=b[i];
        }
        return res;
    }

    /// @brief 多項式 f, g の差を返す
    template<typename T>
    vector<T> Sub(const vector<T>& a, const vector<T>& b) {
        vector<T> res(max(a.size(),b.size()));
        for(int i=0; i<res.size(); i++) {
            if(i<a.size()) res[i]+=a[i];
            if(i<b.size()) res[i]-=b[i];
        }
        return res;
    }

    /// @brief 多項式 f に対し、f*g = 1 なる g を返す
    template<typename T>
    vector<T> Inv(vector<T> f, int len=-1) {
        if(len==-1) len=f.size();
        assert(f[0]!=0);
        vector<T> g={1/f[0]};
        int s=1;
        while(s<len) {
            //g=2g_s-f(g_s)^2(mod x^(2*s))
            //g=g-(fg-1)g
            //(fg-1)=0(mod x^(s))
            vector<T> n_g(s*2,0),f_s(s*2,0);
            g.resize(s*2);
            for(int i=0; i<s*2; i++) {
                if(int(f.size())>i) f_s[i]=f[i];
                n_g[i]=g[i];
            }
            atcoder::internal::butterfly(g);
            atcoder::internal::butterfly(f_s);
            for(int i=0; i<s*2; i++) f_s[i]*=g[i];
            atcoder::internal::butterfly_inv(f_s);
            T iz=1/(T)(s*2);
            for(int i=s; i<s*2; i++) f_s[i]*=iz;
            for(int i=0; i<s; i++) f_s[i]=0;
            atcoder::internal::butterfly(f_s);
            for(int i=0; i<s*2; i++) f_s[i]*=g[i];
            atcoder::internal::butterfly_inv(f_s);
            for(int i=s; i<s*2; i++) n_g[i]-=f_s[i]*iz;
            swap(n_g,g);
            s*=2;
        }
        g.resize(len);
        return g;
    }

    template<typename T>
    vector<T> CyclicConvolution(vector<T> f, vector<T> g) {
        atcoder::internal::butterfly(f);
        atcoder::internal::butterfly(g);
        for(int i=0; i<(int)f.size(); i++) f[i]*=g[i];
        atcoder::internal::butterfly_inv(f);
        T iz=(T)(1)/(T)(f.size());
        for(int i=0; i<(int)f.size(); i++) f[i]*=iz;
        return f;
    }

    /// @brief 多項式 f の積分を返す
    template<typename T>
    vector<T> Integral(vector<T> f) {
        if(f.empty()) return f;
        vector<T> num_inv((int)f.size()+1);
        num_inv[0]=1; num_inv[1]=1;
        auto m=T::mod();
        for(int i=2; i<=(int)f.size(); i++) num_inv[i]=(0-num_inv[m%i])*(T)(m/i);
        f.reserve((int)f.size()+1);
        f.push_back(0);
        for(int i=(int)f.size()-1; i>0; i--) f[i]=f[i-1]*num_inv[i];
        f[0]=0;
        return f;
    }

    /// @brief 多項式 f の微分を返す
    template<typename T>
    vector<T> Differential(vector<T> f) {
        if(f.empty()) return f;
        for(int i=0; i<(int)f.size()-1; i++) f[i]=f[i+1]*(T)(i+1);
        f.pop_back();
        return f;
    }

    /// @brief 多項式 f について、e^f を返す
    template<typename T>
    vector<T> Exp(vector<T> f, int len=-1) {
        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{T(1)};
        assert(!f.empty()&&f[0]==0);
        int s=1;
        //simple
        vector<T> g={T(1)};
        while(s<len) {
            //g'/g
            //A*B
            vector<T> A=g,B=g;
            A=Differential(A);
            B=Inv(B,2*s);
            A.resize(2*s);
            A=CyclicConvolution(A,B);
            A.pop_back();
            A=Integral(A);
            for(int i=0; i<s; i++) A[i]=0;
            for(int i=s; i<s*2; i++) A[i]=(i<(int)f.size()?f[i]:0)-A[i];
            //g_hat=g(1-g+f)
            //g+=B=g*A
            g.resize(2*s);
            B=CyclicConvolution(A,g);
            for(int i=s; i<s*2; i++) g[i]=B[i];
            s*=2;
        }
        g.resize(len);
        return g;
    }

    /// @brief 多項式 f について、log(f) を返す
    template<typename T>
    vector<T> Log(vector<T> f, int len=-1) {
        if(len==-1) len=f.size();
        if(len==0) return{};
        if(len==1) return{T(0)};
        assert(!f.empty()&&f[0]==1);
        vector<T> res=atcoder::convolution(Differential(f),Inv(f,len));
        res.resize(len-1);
        return Integral(res);
    }

    /// @brief 多項式 f^M を返す
    template<class T>
    vector<T> Pow(vector<T> f, ll M, int len=-1) {
        if(len==-1) len=f.size();
        vector<T> res(len,0);
        if(M==0) {
            res[0]=1;
            return res;
        }
        for(int i=0; i<(int)f.size(); i++) {
            if(f[i]==0) continue;
            if(i>(len-1)/M) break;
            vector<T> g((int)f.size()-i);
            T v=(T)(1)/(T)(f[i]);
            for(int j=i; j<(int)f.size(); j++) g[j-i]=f[j]*v;
            ll zero=i*M;
            if(i) len-=i*M;
            g=Log(g,len);
            for(T& x:g) x*=M;
            g=Exp(g,len);
            v=(T)(1)/v;
            T c=1;
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

    //in :DFT(v)(len(v)=z)
    //out:DFT(v)(len(v)=2*z)
    template<typename T>
    void Extend(vector<T>& v) {
        int z=v.size();
        T e=(T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()/(2*z));
        auto cp=v;
        atcoder::internal::butterfly_inv(cp);
        T tmp=(T)(1)/(T)(z);
        for(int i=0; i<z; i++) {
            cp[i]*=tmp;
            tmp*=e;
        }
        atcoder::internal::butterfly(cp);
        for(int i=0; i<z; i++) v.push_back(cp[i]);
    }

    //s.t|v|=2^s(no assert)
    template<typename T>
    void PickEvenOdd(vector<T>& v, int odd) {
        int z=v.size()/2;
        T half=(T)(1)/(T)(2);
        if(odd==0) {
            for(int i=0; i<z; i++) v[i]=(v[i*2]+v[i*2+1])*half;
            v.resize(z);
        }else{
            T e=(T(atcoder::internal::primitive_root_constexpr(T::mod()))).pow(T::mod()/(2*z));
            T ie=T(1)/e;
            vector<T> es={half};
            while((int)es.size()!=z) {
                vector<T> n_es((int)es.size()*2);
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

    /// @brief 多項式 f, g について、`f = gq + r` なる q, r を返す
    template<typename T>
    pair<vector<T>,vector<T>> Div(vector<T> f, vector<T> g) {
        int n=f.size(),m=g.size();
        if(n<m) return{{},f};
        vector<T> r=f;
        reverse(ALL(f)); reverse(ALL(g));
        f.resize(n-m+1);
        vector<T> q=Mul(f,Inv(g,n-m+1));
        q.resize(n-m+1);
        reverse(ALL(q)); reverse(ALL(g));
        r=Sub(r,Mul(q,g));
        while(!q.empty()&&q.back()==0) q.pop_back();
        while(!r.empty()&&r.back()==0) r.pop_back();
        return {q,r};
    }

    /// @brief `[x^k](P/Q)` を返す
    template<typename T>
    T BostonMori(ll k, vector<T> P, vector<T> Q) {
        assert(!Q.empty()&&Q[0]!=0);
        int z=1;
        while(z<(int)max(P.size(),Q.size())) z*=2;
        P.resize(z*2,0); Q.resize(z*2,0);
        atcoder::internal::butterfly(P); atcoder::internal::butterfly(Q);
        //fast
        while(k) {
            //Q(-x)
            vector<T> Q_n(z*2);
            for(int i=0; i<z; i++) {
                Q_n[i*2]=Q[i*2+1];
                Q_n[i*2+1]=Q[i*2];
            }
            for(int i=0; i<z*2; i++) {
                P[i]*=Q_n[i];
                Q[i]*=Q_n[i];
            }
            PickEvenOdd(P,k&1);
            PickEvenOdd(Q,0);
            k/=2;
            if(k==0) break;
            Extend(P);
            Extend(Q);
        }
        T SP=0,SQ=0;
        for(int i=0; i<z; i++) SP+=P[i],SQ+=Q[i];
        return SP/SQ;
    }

    //0=a[i]*c[0]+a[i-1]*c[1]+a[i-2]*c[2]+...+a[i-d]*c[d]
    //a.size()+1==c.size()
    //c[0]=-1?
    //return a[k]
    template<typename T>
    T KthLinear(ll k, vector<T> a, vector<T> c) {
        int d=a.size();
        assert(d+1==int(c.size()));
        vector<T> P=atcoder::convolution(a,c);
        P.resize(d);
        return BostanMori(k,P,c);
    }
}