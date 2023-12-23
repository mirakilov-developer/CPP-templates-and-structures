struct SegTree{
  struct Node{
    ll mx,apply;
    Node(){
      mx = -INFLL, apply = -1;
    }
    Node operator=(const ll x){
      mx = x, apply = -1;
      return *this;
    }
    void merge(const Node &a, const Node &b, int len = 0){
      mx = max(a.mx,b.mx);
    }
    void split(Node &a, Node &b, int len = 0){
      if(apply != -1){
        a.impact(apply,len>>1);
        b.impact(apply,len>>1);
        apply = -1;
      }
    }
    void impact(ll v, int len = 0){
      mx = v;
      apply = v;
    }
  };

  vector<Node> tree;
  Node NEUTRAL;
  int n,N;
  SegTree(vector<ll> &a){
    n = a.size();
    N = 1<<(32-__builtin_clz(n-1));
    tree.resize(2*N);
    for(int i = N; i < N+n; ++i) tree[i] = a[i-N];
    for(int i = N-1; i > 0; --i) tree[i].merge(tree[i<<1],tree[i<<1|1]);
  }
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
  ll mx(int ql, int qr){ // [ql, qr)
    Node ans = range_query(1,0,N,ql,qr);
    return ans.mx;
  }
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
  void apply(int ql, int qr, ll v){
    range_update(1,0,N,ql,qr,v);
  }
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
  int find_greater_or_equal(int ql, int qr, ll x, bool isFirst){   
    function<bool(const Node&)> check = [&x](const Node& nd) {
      return x <= nd.mx;
    };
    if(isFirst) return find_first(1,0,N,ql,qr,check);
    return find_last(1,0,N,ql,qr,check);
  }
};