// Pathetic

#include <bits/stdc++.h>

#define trav(i,n) for(int i = 0; i < (n); ++i)
#define pb push_back
#define se second
#define fi first
#define all(x) (x).begin(),(x).end()

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

const ld PI = 3.141592653589793;
const ll MOD = 1e9+7;
const int INF = 1e9;
const ll INFLL = 4e18;
const double EPS = 1e-9;
const int SIZE = 1000*1007;

void solve(int NT){
    
}

void setIn(string s) {freopen(s.c_str(), "r", stdin);}
void setOut(string s) {freopen(s.c_str(), "w", stdout);}

#define TESTCASES
int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
    #ifdef TESTCASES
        cin >> t;
    #endif
    
    for(int i = 1; i <= t; ++i){
        solve(i);
        cout << "\n";
    }
}
