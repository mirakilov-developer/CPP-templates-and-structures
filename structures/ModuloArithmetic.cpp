#include <iostream>

using namespace std;

const int MOD = 1e9+7;
// Arithmetic by MODULO
// ver 0.4.0
struct Mint{
    Mint binpow(int z, int b){
        Mint ans = 1;
        Mint a = z;
        while(b){
            if(b&1) ans *= a;
            a *= a;
            b >>= 1;
        }
        
        return ans;
    }
    
    int inverse(int z){
        assert(__gcd(z,MOD) == 1);
        return binpow(z,MOD-2).x;
    }
    
    int x;
    Mint(int a=0):x(a){}
    
    Mint& operator=(const Mint &y){x = y.x; return *this;}
    Mint& operator=(int a){x = a; return *this;}
    
    Mint operator+(const Mint &y)const{return Mint((1LL*x+y.x)%MOD);}
    Mint operator+(int a)const{return Mint((1LL*x+a)%MOD);}
    Mint& operator+=(const Mint &y){x = (1LL*x+y.x)%MOD; return *this;}
    Mint& operator+=(int a){x = (1LL*x+a)%MOD; return *this;}
    
    Mint operator-(const Mint &y)const{return Mint((1LL*x-y.x+MOD)%MOD);}
    Mint operator-(int a)const{return Mint((1LL*x-a+MOD)%MOD);}
    Mint& operator-=(const Mint &y){x = (1LL*x-y.x+MOD)%MOD; return *this;}
    Mint& operator-=(int a){x = (1LL*x-a+MOD)%MOD; return *this;}
    
    Mint operator*(const Mint &y)const{return Mint((1LL*x*y.x)%MOD);}
    Mint operator*(int a)const{return Mint((1LL*x*a)%MOD);}
    Mint& operator*=(const Mint &y){x = (1LL*x*y.x)%MOD; return *this;}
    Mint& operator*=(int a){x = (1LL*x*a)%MOD; return *this;}
    
    Mint operator/(const Mint &y){return Mint((1LL*x*inverse(y.x))%MOD);}
    Mint operator/(int a){return Mint((1LL*x*inverse(a))%MOD);}
    Mint& operator/=(const Mint &y){x = (1LL*x*inverse(y.x))%MOD; return *this;}
    Mint& operator/=(int a){x = (1LL*x*inverse(a))%MOD; return *this;}
};
ostream& operator<<(ostream& os, const Mint& y){os << y.x;return os;}

int main() {
    Mint a = 300;
    cout << a+5;
    
    return 0;
}
