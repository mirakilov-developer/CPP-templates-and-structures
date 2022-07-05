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


// Segment Tree structure.
// Top to bottom. Version 2.0.0
// change:
//      Node structure 
//      Constructor (if need)
//      Add extra interface functions (if need)

// save max, propogate addition version
struct SegTree{
    struct Node{
        // node variables.
        ll mx,add;
        
        // neutral element.
        Node(){
            mx = -INFLL;
            add = 0;
        }
        
        // gets value from array.
        Node operator=(const ll x){
            mx = x, add = 0;
            return *this;
        }
        
        // merges two sons to mother.
        void merge(const Node &a, const Node &b, int len = 0){
            mx = max(a.mx,b.mx);
        }
        
        // splits update from mother to sons.
        void split(Node &a, Node &b, int len = 0){
            if(add){
                a.impact(add,len>>1);
                b.impact(add,len>>1);
                add = 0;
            }
        }
        
        // updates.
        void impact(ll v, int len = 0){
            mx += v;
            add += v;
        }
    };
    
    // variables: tree, neutral element and sizes.
    vector<Node> tree;
    Node NEUTRAL;
    int n,N;
    
    // constructor: uses to build segment tree.
    SegTree(vector<ll> &a){
        n = a.size();
        N = 1<<(32-__builtin_clz(n-1));
        tree.resize(2*N);
        
        for(int i = N; i < N+n; ++i) tree[i] = a[i-N];
        for(int i = N-1; i > 0; --i) tree[i].merge(tree[i<<1],tree[i<<1|1]);
    }
    
    
    // range_query: calculates everything on range.
    Node range_query(int i, int l, int r, int ql, int qr){
        if(qr <= l || r <= ql) return NEUTRAL;
        if(ql <= l && r <= qr) return tree[i];
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        int mid = (l+r)>>1;
        
        Node ans;
        ans.merge(range_query(i<<1  ,l,mid,ql,qr),
                  range_query(i<<1|1,mid,r,ql,qr),
                  r-l);
        return ans;
    }
    
    // interface to range_query:
    // call range_query then ask anything.
    ll mx(int ql, int qr){
        Node ans = range_query(1,0,N,ql,qr);
        return ans.mx;
    }
    
    // range_update: update the range.
    void range_update(int i, int l, int r, int ql, int qr, ll v){
        if(qr <= l || r <= ql) return;
        if(ql <= l && r <= qr) {
            tree[i].impact(v,r-l);
            return;
        }
        
        int mid = (l+r)>>1;
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        range_update(i<<1,  l,mid,ql,qr,v);
        range_update(i<<1|1,mid,r,ql,qr,v);
        tree[i].merge(tree[i<<1],tree[i<<1|1],r-l);
    }

    // interface for range_update:
    // change name not to confuse.
    void add(int ql, int qr, ll v){
        range_update(1,0,N,ql,qr,v);
    }
};

// SOLVED
// https://acmp.ru/asp/do/index.asp?main=task&id_course=2&id_section=20&id_topic=45&id_problem=599 
void solve(int NT){
    int n,k,m; cin >> n >> k;
    vector<ll> a(n,0);
    SegTree sg(a);
    cin >> m;
    while(m--){
        int l,r; cin >> l >> r;
        if(sg.mx(l,r) == k) cout << "No\n";
        else {
            cout << "Yes\n";
            sg.add(l,r,1);    
        }
    }
}

// #define TESTCASES
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
