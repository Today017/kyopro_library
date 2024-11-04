#include"../../kyopro_library/template.hpp"
#include<atcoder/modint>
#include<atcoder/convolution>
#include"../../kyopro_library/mod/cmb.hpp"

template<typename T>
struct FPS:vector<T>{
	using vector<T>::vector;
	using vector<T>::operator=;
	static Combination<T>fc;
	FPS operator-()const{
		FPS res(*this);
		for(auto&e:res)e=-e;
		return res;
	}
	FPS&operator*=(const T&g){
		for(auto&e:*this)e*=g;
		return*this;
	}
	FPS&operator/=(const T&g){
		assert(g!=T(0));
		*this*=g.inv();
		return*this;
	}
	FPS&operator+=(const FPS&g){
		int n=this->size(),m=g.size();
		for(int i=0;i<min(n,m);i++)(*this)[i]+=g[i];
		return*this;
	}
	FPS&operator-=(const FPS&g){
		int n=this->size(),m=g.size();
		for(int i=0;i<min(n,m);i++)(*this)[i]-=g[i];
		return*this;
	}
	FPS&operator<<=(const int d){
		int n=this->size();
		if(d>=n)*this=FPS(n);
		this->insert(this->begin(),d,0);
		this->resize(n);
		return*this;
	}
	FPS&operator>>=(const int d){
		int n=this->size();
		this->erase(this->begin(),this->begin()+min(n,d));
		this->resize(n);
		return*this;
	}
	FPS inv(int d=-1)const{
		int n=this->size();
		assert(n!=0&&(*this)[0]!=0);
		if(d==-1)d=n;
		assert(d>=0);
		FPS res;
		res.push_back((*this)[0].inv());
		for(int m=1;m<d;m*=2){
			FPS f(this->begin(),this->begin()+min(n,2*m));
			FPS g(res);
			f.resize(2*m);
			atcoder::internal::butterfly(f);
			g.resize(2*m);
			atcoder::internal::butterfly(g);
			for(int i=0;i<2*m;i++)f[i]*=g[i];
			atcoder::internal::butterfly_inv(f);
			f.erase(f.begin(),f.begin()+m);
			f.resize(2*m);
			atcoder::internal::butterfly(f);
			for(int i=0;i<2*m;i++)f[i]*=g[i];
			atcoder::internal::butterfly_inv(f);
			T iz=T(2*m).inv();
			iz*=-iz;
			for(int i=0;i<m;i++)f[i]*=iz;
			res.insert(res.end(),f.begin(),f.begin()+m);
		}
		res.resize(d);
		return res;
	}
	FPS&multiply_inplace(const FPS&g,int d=-1){
		int n=this->size();
		if(d==-1)d=n;
		assert(d>=0);
		*this=atcoder::convolution(move(*this),g);
		this->resize(d);
		return*this;
	}
	FPS multiply(const FPS&g,const int d=-1)const{
		return FPS(*this).multiply_inplace(g,d);
	}
	FPS&divide_inplace(const FPS&g,int d=-1){
		int n=this->size();
		if(d==-1)d=n;
		assert(d>=0);
		*this=atcoder::convolution(move(*this),g.inv(d));
		this->resize(d);
		return*this;
	}
	FPS divide(const FPS&g,const int d=-1)const{
		return FPS(*this).divide_inplace(g,d);
	}
	FPS&multiply_inplace(vector<pair<int,T>>g){
		int n=this->size();
		auto[d,c]=g.front();
		if(d==0){
			g.erase(g.begin());
		}else{
			c=0;
		}
		for(int i=n-1;i>=0;i--){
			(*this)[i]*=c;
			for(auto&[j,b]:g){
				if(j>i)break;
				(*this)[i]+=(*this)[i-j]*b;
			}
		}
		return*this;
	}
	FPS multiply(const vector<pair<int,T>>&g)const{
		return FPS(*this).multiply_inplace(g);
	}
	FPS&divide_inplace(vector<pair<int,T>>g){
		int n=this->size();
		auto[d,c]=g.front();
		assert(d==0&&c!=T(0));
		T ic=c.inv();
		g.erase(g.begin());
		for(int i=0;i<n;i++){
			for(auto&[j,b]:g){
				if(j>i)break;
				(*this)[i]-=(*this)[i-j]*b;
			}
			(*this)[i]*=ic;
		}
		return*this;
	}
	FPS divide(const vector<pair<int,T>>&g)const{
		return FPS(*this).divide_inplace(g);
	}
	void multiply_inplace(const int d,const T c){
		int n=this->size();
		if(c==T(1)){
			for(int i=n-d-1;i>=0;i--)(*this)[i+d]+=(*this)[i];
		}else if(c==T(-1)){
			for(int i=n-d-1;i>=0;i--)(*this)[i+d]-=(*this)[i];
		}else{
			for(int i=n-d-1;i>=0;i--)(*this)[i+d]+=(*this)[i]*c;
		}
	}
	void divide_inplace(const int d,const T c){
		int n=this->size();
		if(c==T(1)){
			for(int i=0;i<n-d;i++)(*this)[i+d]-=(*this)[i];
		}else if(c==T(-1)){
			for(int i=0;i<n-d;i++)(*this)[i+d]+=(*this)[i];
		}else{
			for(int i=0;i<n-d;i++)(*this)[i+d]-=(*this)[i]*c;
		}
	}
	T eval(const T&a)const{
		T x(1),res(0);
		for(auto e:*this){
			res+=e*x;
			x*=a;
		}
		return res;
	}
	FPS&integral_inplace(){
		int n=this->size();
		assert(n>0);
		if(n==1)return*this=FPS{0};
		this->insert(this->begin(),0);
		this->pop_back();
		vector<T>inv(n);
		inv[1]=1;
		int p=T::mod();
		for(int i=2;i<n;i++)inv[i]=-inv[p%i]*(p/i);
		for(int i=2;i<n;i++)(*this)[i]*=inv[i];
		return*this;
	}
	FPS integral()const{return FPS(*this).integral_inplace();}
	FPS&derivative_inplace(){
		int n=this->size();
		assert(n>0);
		for(int i=2;i<n;i++)(*this)[i]*=i;
		this->erase(this->begin());
		this->push_back(0);
		return*this;
	}
	FPS derivative()const{return FPS(*this).derivative_inplace();}
	FPS&log_inplace(int d=-1){
		int n=this->size();
		assert(n>0&&(*this)[0]==1);
		if(d==-1)d=n;
		assert(d>=0);
		if(d<n)this->resize(d);
		FPS f_inv=this->inv();
		this->derivative_inplace();
		this->multiply_inplace(f_inv);
		this->integral_inplace();
		return*this;
	}
	FPS log(const int d=-1)const{return FPS(*this).log_inplace(d);}
	FPS&exp_inplace(int d=-1){
		int n=this->size();
		assert(n>0&&(*this)[0]==0);
		if(d==-1)d=n;
		assert(d>=0);
		FPS g{1},g_fft{1,1};
		(*this)[0]=1;
		this->resize(d);
		FPS h_drv(this->derivative());
		for(int m=2;m<d;m*=2){
			FPS f_fft(this->begin(),this->begin()+m);
			f_fft.resize(2*m);
			atcoder::internal::butterfly(f_fft);
			{
				FPS_g(m);
				for(int i=0;i<m;i++)_g[i]=f_fft[i]*g_fft[i];
				atcoder::internal::butterfly_inv(_g);
				_g.erase(_g.begin(),_g.begin()+m/2);
				_g.resize(m);
				atcoder::internal::butterfly(_g);
				for(int i=0;i<m;i++)_g[i]*=g_fft[i];
				atcoder::internal::butterfly_inv(_g);
				_g.resize(m/2);
				_g/=T(-m)*m;
				g.insert(g.end(),_g.begin(),_g.begin()+m/2);
			}
			FPS t(this->begin(),this->begin()+m);
			t.derivative_inplace();
			{
				FPS r{h_drv.begin(),h_drv.begin()+m-1};
				r.resize(m);
				atcoder::internal::butterfly(r);
				for(int i=0;i<m;i++)r[i]*=f_fft[i];
				atcoder::internal::butterfly_inv(r);
				r/=-m;
				t+=r;
				t.insert(t.begin(),t.back());
				t.pop_back();
			}
			if(2*m<d){
				t.resize(2*m);
				atcoder::internal::butterfly(t);
				g_fft=g;
				g_fft.resize(2*m);
				atcoder::internal::butterfly(g_fft);
				for(int i=0;i<2*m;i++)t[i]*=g_fft[i];
				atcoder::internal::butterfly_inv(t);
				t.resize(m);
				t/=2*m;
			}else{
				FPS g1(g.begin()+m/2,g.end());
				FPS s1(t.begin()+m/2,t.end());
				t.resize(m/2);
				g1.resize(m);
				atcoder::internal::butterfly(g1);
				t.resize(m);
				atcoder::internal::butterfly(t);
				s1.resize(m);
				atcoder::internal::butterfly(s1);
				for(int i=0;i<m;i++)s1[i]=g_fft[i]*s1[i]+g1[i]*t[i];
				for(int i=0;i<m;i++)t[i]*=g_fft[i];
				atcoder::internal::butterfly_inv(t);
				atcoder::internal::butterfly_inv(s1);
				for(int i=0;i<m/2;i++)t[i+m/2]+=s1[i];
				t/=m;
			}
			FPS v(this->begin()+m,this->begin()+min<int>(d,2*m));
			v.resize(m);
			t.insert(t.begin(),m-1,0);
			t.push_back(0);
			t.integral_inplace();
			for(int i=0;i<m;i++)v[i]-=t[m+i];
			v.resize(2*m);
			atcoder::internal::butterfly(v);
			for(int i=0;i<2*m;i++)v[i]*=f_fft[i];
			atcoder::internal::butterfly_inv(v);
			v.resize(m);
			v/=2*m;
			for(int i=0;i<min(d-m,m);i++)(*this)[m+i]=v[i];
		}
		return*this;
	}
	FPS exp(const int d=-1)const{return FPS(*this).exp_inplace(d);}
	FPS&pow_inplace(const ll k,int d=-1){
		int n=this->size();
		if(d==-1)d=n;
		assert(d>=0&&k>=0);
		if(k==0){
			*this=FPS(d);
			if(d>0)(*this)[0]=1;
			return*this;
		}
		int l=0;
		while(l<n&&(*this)[l]==0)l++;
		if(l>(d-1)/k){
			*this=FPS(d);
			return*this;
		}
		T c=(*this)[l];
		this->erase(this->begin(),this->begin()+l);
		*this/=c;
		this->log_inplace(d-l*k);
		*this*=k;
		this->exp_inplace();
		*this*=c.pow(k);
		this->insert(this->begin(),l*k,0);
		return*this;
	}
	FPS pow(const ll k,const int d=-1)const{return FPS(*this).pow_inplace(k,d);}
	FPS&shift_inplace(const T c){
		if(fc.fact.empty())fc=Combination<T>(1000000);
		int n=this->size();
		for(int i=0;i<n;i++)(*this)[i]*=fc.fact[i];
		for(int i=n-1;i>=0;i--)(*this)[i+1]+=(*this)[i]*c;
		reverse(this->begin(),this->end());
		FPS g(n);
		T cp=1;
		for(int i=0;i<n;i++){
			g[i]=cp*fc.factinv[i];
			cp*=c;
		}
		this->multiply_inplace(g,n);
		reverse(this->begin(),this->end());
		for(int i=0;i<n;i++)(*this)[i]*=fc.factinv[i];
		return*this;
	}
	FPS shift(const T c)const{return FPS(*this).shift_inplace(c);}
	FPS operator*(const T&g)const{return FPS(*this)*=g;}
	FPS operator/(const T&g)const{return FPS(*this)/=g;}
	FPS operator+(const FPS&g)const{return FPS(*this)+=g;}
	FPS operator-(const FPS&g)const{return FPS(*this)-=g;}
	FPS operator<<(const int d)const{return FPS(*this)<<=d;}
	FPS operator>>(const int d)const{return FPS(*this)>>=d;}
};