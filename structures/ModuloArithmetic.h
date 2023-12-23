namespace NT {
	template<class T, int mod>
	struct modint {
		T x = 0;

		modint(){};
		modint( T a ):x(norm(a)){};
		T norm( T a ) {
			if(a >= mod) a = a % mod;
			else if(a < 0) a = a % mod + mod;
			return a;
		}
		void norm() { x = norm(x); }

		bool operator ==( const modint &m ) { return x == m.x; }
		bool operator !=( const modint &m ) { return !(*this == m); }
	
		modint& operator +=( const modint &m ){ x = norm(x + m.x); return *this; }
		modint& operator -=( const modint &m ){ x = norm(x - m.x); return *this; }
		modint& operator *=( const modint &m ){ x = 1LL * m.x * x % mod; return *this; }
		modint& operator /=( const modint &m ){ return *this *= inv( m ); }
	
		modint& operator +=( const T &y ){ x = norm(x + y); return *this; }
		modint& operator -=( const T &y ){ x = norm(x - y); return *this; }
		modint& operator *=( const T &y ){ x = 1LL * norm(y) * x % mod; return *this; }
		modint& operator /=( const T &y ){ return *this *= inv( modint( y ) ); }
		
		modint operator +( const modint &m ) { modint ans = modint(*this); return ans += m; }
		modint operator -( const modint &m ) { modint ans = modint(*this); return ans -= m; }
		modint operator *( const modint &m ) { modint ans = modint(*this); return ans *= m; }
		modint operator /( const modint &m ) { modint ans = modint(*this); return ans /= m; }
	
		modint operator +( const T &y ) { modint ans = modint(*this); return ans += y; }
		modint operator -( const T &y ) { modint ans = modint(*this); return ans -= y; }
		modint operator *( const T &y ) { modint ans = modint(*this); return ans *= y; }
		modint operator /( const T &y ) { modint ans = modint(*this); return ans /= y; }
	
		friend modint inv( modint m ){ return binpow( m, mod - 2 ); }
		friend modint binpow( modint m, long long n ){ if(n < 0) return binpow(inv(m), -n); modint res{1}; while( n ){ if( n & 1 ) res *= m; m *= m; n >>= 1; } return res; }
		friend modint mul( modint m, long long n ){ modint res; while( n ){ if( n & 1 ) res += m; m += m; n >>= 1; } return res; }
		
		friend ostream & operator << ( ostream &os, const modint& m ){ return os << m.x; }
		friend istream & operator >> ( istream &is, modint& m ){ is >> m.x; m.norm(); return is; }
	};
};

using namespace NT;
using mint = modint<int, (int)1e9 + 7>;