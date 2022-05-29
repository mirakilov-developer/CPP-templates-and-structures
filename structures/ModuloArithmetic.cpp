#include <iostream>

using namespace std;

const int MOD = 1e9+7;
// Arithmetic by MODULO
// ver 0.6.0
struct Mint{
    Mint binpow(ll z, ll b){
        Mint ans = 1;
        Mint a = z;
        while(b){
            if(b&1) ans *= a;
            a *= a;
            b >>= 1;
        }
        
        return ans;
    }
    
    ll inverse(ll z){
        assert(__gcd(z,MOD) == 1);
        return binpow(z,MOD-2).x;
    }
    
    ll x;
    Mint(ll a=0):x(a){}
    
    Mint& operator=(const Mint &y){x = y.x; return *this;}
    Mint& operator=(ll a){x = a; return *this;}
    
    Mint operator+(const Mint &y)const{return Mint((x+y.x)%MOD);}
    Mint operator+(ll a)const{return Mint((x+a)%MOD);}
    Mint& operator+=(const Mint &y){x = (x+y.x)%MOD; return *this;}
    Mint& operator+=(ll a){x = (x+a)%MOD; return *this;}
    
    Mint operator-(const Mint &y)const{return Mint((x-y.x+MOD)%MOD);}
    Mint operator-(ll a)const{return Mint((x-a+MOD)%MOD);}
    Mint& operator-=(const Mint &y){x = (x-y.x+MOD)%MOD; return *this;}
    Mint& operator-=(ll a){x = (x-a+MOD)%MOD; return *this;}
    
    Mint operator*(const Mint &y)const{return Mint((x*y.x)%MOD);}
    Mint operator*(ll a)const{return Mint((x*a)%MOD);}
    Mint& operator*=(const Mint &y){x = (x*y.x)%MOD; return *this;}
    Mint& operator*=(ll a){x = (x*a)%MOD; return *this;}
    
    Mint operator/(const Mint &y){return Mint((x*inverse(y.x))%MOD);}
    Mint operator/(ll a){return Mint((x*inverse(a))%MOD);}
    Mint& operator/=(const Mint &y){x = (x*inverse(y.x))%MOD; return *this;}
    Mint& operator/=(ll a){x = (x*inverse(a))%MOD; return *this;}
    
    bool operator==(ll a){ return x == a%MOD;}
    bool operator==(const Mint &y){ return x == y.x;}
    
    bool operator>(ll a){ return x > a%MOD;}
    bool operator>(const Mint &y){ return x > y.x;}
    
    bool operator<(ll a){ return x < a%MOD;}
    bool operator<(const Mint &y){ return x < y.x;}
    
    bool operator>=(ll a){ return x >= a%MOD;}
    bool operator>=(const Mint &y){ return x >= y.x;}
    
    bool operator<=(ll a){ return x <= a%MOD;}
    bool operator<=(const Mint &y){ return x <= y.x;}
};
ostream& operator<<(ostream& os, const Mint& y){os << y.x;return os;}
istream& operator>>(istream& is, Mint& y){is >> y.x;return is;}

int main() {
    Mint a = 300;
    cout << a+5;
    
    return 0;
}
