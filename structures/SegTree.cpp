// Segment Tree structure.
// Top to bottom. Version 2.5.0
// change:
//      Node structure 
//      Constructor (if need)
//      Add extra interface functions (if need)

// NOTE: indexation of tree nodes from 1
//       indexation of range (array elements) from 0
//       work with semi-interval, a.k.a [l,r)

// Type of queries:
// save - max; propogate - apply; find - smaller or equal;
struct SegTree{
    struct Node{
        // node variables.
        ll mx,apply;
        
        // neutral element.
        Node(){
            mx = -INFLL, apply = -1;
        }
        
        // gets value from array.
        Node operator=(const ll x){
            mx = x, apply = -1;
            return *this;
        }
        
        // merges two sons to mother.
        void merge(const Node &a, const Node &b, int len = 0){
            mx = max(a.mx,b.mx);
        }
        
        // splits update from mother to sons.
        void split(Node &a, Node &b, int len = 0){
            if(apply != -1){
                a.impact(apply,len>>1);
                b.impact(apply,len>>1);
                apply = -1;
            }
        }
        
        // updates.
        void impact(ll v, int len = 0){
            mx = v;
            apply = v;
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
    
    // for there and after
    // [ql,qr) asking range
    // i       node number
    // [l,r)   range of the node
    
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
    
    // range_update: updates the range with parameter v.
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
    void apply(int ql, int qr, ll v){
        range_update(1,0,N,ql,qr,v);
    }
    
    // find_first:
    // finds first index of element on range that satisfies "check()" condition
    // returns n if there is no such element
    int find_first(int i, int l, int r, int ql, int qr, function<bool(const Node&)> &check){
        if(qr <= l || r <= ql) return n;
        if(ql <= l && r <= qr) {
            if(!check(tree[i])) return n;
            if(r-l == 1) return l;
        }
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        
        int mid = (l+r)>>1;
        int ans = find_first(i<<1,l,mid,ql,qr,check);
        if(ans == n) ans = find_first(i<<1|1,mid,r,ql,qr,check);
        
        return ans;
    }
    
    // find_last:
    // finds last index of element on range that satisfies "check()" condition
    // returns -1 if there is no such element
    int find_last(int i, int l, int r, int ql, int qr, function<bool(const Node&)> &check){
        if(qr <= l || r <= ql) return -1;
        if(ql <= l && r <= qr) {
            if(!check(tree[i])) return -1;
            if(r-l == 1) return l;
        }
        
        tree[i].split(tree[i<<1],tree[i<<1|1],r-l);
        
        int mid = (l+r)>>1;
        int ans = find_last(i<<1|1,mid,r,ql,qr,check);
        if(ans == -1) ans = find_last(i<<1,l,mid,ql,qr,check);
        
        return ans;
    }
    
    // interface for find_first or find_last:
    // isFirst  true  if find_first
    //          false if find_last
    // change name not to confuse.
    
    int find_smaller_or_equal(int ql, int qr, ll x,bool isFirst){
        
        function<bool(const Node&)> check = [&x](const Node& nd){
            return x <= nd.mx;
        };
        
        if(isFirst) return find_first(1,0,N,ql,qr,check);
        return find_last(1,0,N,ql,qr,check);
    }
};