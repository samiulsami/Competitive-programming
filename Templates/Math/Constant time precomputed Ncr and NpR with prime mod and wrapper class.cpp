template<const int MOD = 0>
struct ModInt{
	///credits: https://codeforces.com/blog/entry/63903
	int val;
	ModInt(int64_t v = 0){ val = v%MOD; if(val<0)val+=MOD;}
	ModInt(int64_t a, int64_t b):val(0){ *this += a; *this /= b;}
	ModInt& operator+=(ModInt const &b){val+=b.val; if(val>=MOD)val-=MOD; return *this;}
	ModInt& operator-=(ModInt const &b){val-=b.val; if(val<0)val+=MOD; return *this;}
	ModInt& operator*=(ModInt const &b){val=(1LL*val*b.val)%MOD; return *this;}
	friend ModInt bigmod(ModInt a, int64_t b){ModInt ret = 1;while(b){if(b&1)ret *= a;a*=a;b>>=1;}return ret;}
	friend ModInt inverse(ModInt a){return bigmod(a,MOD-2);}
	ModInt& operator/=(ModInt const& b){return *this *= inverse(b); }
	friend ModInt operator+(ModInt a, ModInt const b){return a += b;}
	friend ModInt operator-(ModInt a, ModInt const b){return a -= b; }
	friend ModInt operator-(ModInt const a){return 0-a; }
	friend ModInt operator*(ModInt a, ModInt const b){return a *= b;}
	friend ModInt operator/(ModInt a, ModInt const b){return a /= b;}
	friend std::ostream& operator<<(std::ostream& os, ModInt const& a){return os << a.val;}
	friend std::istream& operator>>(std::istream& is, ModInt &a){int64_t x;is>>x;a = ModInt(x);return is;}
	friend bool operator==(ModInt const& a, ModInt const& b){return a.val == b.val;}
	friend bool operator!=(ModInt const& a, ModInt const& b){return a.val != b.val;}
};

const int MOD = 1e9+7;
using mint = ModInt<MOD>;

struct PNC{
	static const int pncSZ=1e7+5;
	mint fact[pncSZ],factInv[pncSZ];
	PNC(){
		fact[0]=mint(1);
		for(int i=1; i<pncSZ; i++)fact[i]=fact[i-1]*mint(i);
		factInv[pncSZ-1]=mint(1)/fact[pncSZ-1];
		for(int i=pncSZ-1; i>0; i--)factInv[i-1]=mint(i)*factInv[i];
	}
	inline mint ncr(int n, int r){
		if(n<r)return 0;
		return fact[n]*factInv[r]*factInv[n-r];
	}
	inline mint npr(int n, int r){
		if(n<r)return 0;
		return fact[n]*factInv[n-r];
	}
}C;