// MDSPro

#include <bits/stdc++.h>

#define trav(i,n) for(int i = 0; i < (n); i++)
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

// MO'S ALGORITHM TO PROCCESS OFFLINE QUERIES IN O((n+m)*sqrt(n))
// DQUERY VERSION (count distinct numbers in range)
// TOUCH NOTHING, ONLY ###### (and int,ll and etc.)
// **NOTE WORK WITH [l,r)
struct MO{
    
    struct Query{
        int l,r,id;
    };
    
    // ######
    // CHANGE EVERY THING
    // ######
    struct Range_Handler{ // the structure to handle queries on range
        vector<int> a;
        
        int ans = 0;
        Range_Handler(int upper_range){
            a.assign(upper_range+1,0);
        }
        
        // remove from range
        void rem(int x){
            a[x]--;
            if(a[x] == 0) ans--;
        }
        
        // add to range
        void add(int x){
            a[x]++;
            if(a[x] == 1) ans++;
        }
        
        // get ans in this range
        int get_ans(){
            return ans;
        }
    };
    
    // main code
    // call as, get(arr, queries, extra)
    vector<int> get(vector<int> &arr, vector<pii> &initial, int extra = 0){
        int n = initial.size();
        int BS = sqrt(n);
        
        vector<Query> qs;
        for(int i = 0; i < n; ++i){
            qs.pb({initial[i].fi,initial[i].se,i});
        }
        
        sort(all(qs),[&](const Query &a, const Query &b)->bool{
            return (a.l/BS < b.l/BS) || (a.l/BS == b.l/BS && a.r < b.r);
        });
        
        vector<int> ans(n);
        Range_Handler observer(extra);
        
        int l = 0, r = 0;
        for(int i = 0; i < n; ++i){
            int x = qs[i].l, y = qs[i].r;
            
            while(r < y) observer.add(arr[r++]);
            while(l < x) observer.rem(arr[l++]);
            while(l > x) observer.add(arr[--l]);
            while(r > y) observer.rem(arr[--r]);
            
            ans[qs[i].id] = observer.get_ans();
        }
        
        return ans;
    }
    
} query_manager;


// DRIVER aka EXAMPLE
// ACTUALLY DQUERY SOLUTION
void solve(int NT){
    int n,q; cin >> n;
    vector<int> arr(n); for(auto &x: arr) cin >> x;
    
    cin >> q;
    vector<pii> a(q); for(auto &x: a) {
        cin >> x.fi >> x.se;
        x.fi--;
    }
    
    vector<int> ans = query_manager.get(arr,a,*max_element(all(arr)));
    for(auto x: ans) cout << x << "\n";
}


// #define TESTCASES
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    #ifdef TESTCASES
        cin >> t;
    #endif
    
    for(int i = 1; i <= t; ++i){
        solve(i);
        cout << "\n";
    }
}
