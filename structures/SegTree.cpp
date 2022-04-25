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
// Top to bottom. Version 1.0
// change only:
//      Node structure 
//      Constructor (if need)
//      Name of functions
struct SegTree{
    struct Node{
        // Node variables
        ll val,add;
        
        // Neutral element
        Node(){
            val = -INFLL;
            add = 0;
        }
        
    //     // Need for point_ask and building via array
        Node(ll x){
            add = 0;
            val = x;
        }
        Node operator=(const ll x){
            val = x;
            add = 0;
            return *this;
        }
        
        // Merge
        void merge(Node &a, Node &b, int len = 0){
            val = max(a.val,b.val);
        }
        
        // Split. Need only in lazy
        void split(Node &a, Node &b, int len){
            if(add){
                a.impact(add,len/2);
                b.impact(add,len/2);
                add = 0;
            }
        }
        
        // Impact. Need only in lazy
        void impact(ll v, int len = 0){
            val += v;
            add += v;
        }
    };
    
    // Constructor (built)
    vector<Node> tree;
    Node NEUTRAL;
    int N;
    SegTree(vector<ll> a){
        int n = a.size();
        N = 1<<(32-__builtin_clz(n-1));
        tree.resize(2*N);
        
        for(int i = N; i < N+n; ++i) tree[i] = a[i-N];
        int h = N/2;
        while(h){
            for(int i = 2*h-1; i >= h; --i) tree[i].merge(tree[i<<1],tree[i<<1|1],N/h);
            h /= 2;
        }
    }
    
    
    /* queries ********************************************************
    *******************************************************************
    ******************************************************************/
    // point_ask
    ll point_ask(int i, int l, int r, int q){
        if(q < l || r <= q) return NEUTRAL.val;
        if(r-l == 1) return tree[i].val;
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        
        int mid = (l+r)/2;
        
        Node left (point_ask(i<<1  ,l,mid,q));
        Node right(point_ask(i<<1|1,mid,r,q));
        Node ans; ans.merge(left,right);
        return ans.val;
    }
    
    // point_ask, driver
    ll point_ask(int q){
        return point_ask(1,0,N,q);
    }
    
    // point_update
    void point_update(int i, int l, int r, int q, ll v){
        if(q < l || r <= q) return;
        if(r-l == 1) {
            tree[i] = v;
            return;
        }
        
        int mid = (l+r)/2;
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        point_update(i<<1  ,l,mid,q,v);
        point_update(i<<1|1,mid,r,q,v);
        tree[i].merge(tree[i<<1],tree[i<<1|1],r-l);
    }
    
    // point_ask, driver
    void point_update(int q, ll v){
        point_update(1,0,N,q,v);
    }
    
    // range_ask
    ll range_ask(int i, int l, int r, int ql, int qr){
        if(qr <= l || r <= ql) return NEUTRAL.val;
        if(ql <= l && r <= qr) return tree[i].val;
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        
        int mid = (l+r)/2;
        
        Node left (range_ask(i<<1  ,l,mid,ql,qr));
        Node right(range_ask(i<<1|1,mid,r,ql,qr));
        Node ans; ans.merge(left,right);
        return ans.val;
    }
    
    // range_ask, driver
    ll range_ask(int ql, int qr){
        return range_ask(1,0,N,ql,qr);
    }
    
    /* lazy zone ******************************************************
    *******************************************************************
    ******************************************************************/
    // // range_update
    void range_update(int i, int l, int r, int ql, int qr, ll v){
        if(qr <= l || r <= ql) return;
        if(ql <= l && r <= qr) {
            tree[i].impact(v,r-l);
            return;
        }
        
        int mid = (l+r)/2;
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        range_update(i<<1,  l,mid,ql,qr,v);
        range_update(i<<1|1,mid,r,ql,qr,v);
        tree[i].merge(tree[i<<1],tree[i<<1|1],r-l);
    }

    // range_update, driver
    void range_update(int ql, int qr, ll v){
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
        if(sg.range_ask(l,r) == k) cout << "No\n";
        else {
            cout << "Yes\n";
            sg.range_update(l,r,1);    
        }
    }
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
