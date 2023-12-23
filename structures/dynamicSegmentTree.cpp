const int MAXN = 2e8; // 200 MB
static char buf[MAXN];
void* operator new(size_t s) {
	static size_t i = sizeof buf;
	assert(s < i);
	return (void*)&buf[i -= s];
}
void operator delete(void*) {}
 
const int N = 1 << 30;
struct Node {
  int sum, apply;
  Node *left, *right;
  Node(): sum(0), apply(0), left(NULL), right(NULL) {}
};
void impact(Node *& x, int v, int len) {
  if(x == NULL) x = new Node();
  x->apply = v; x->sum = v * len;
}
void split(Node *& x, int len) {
  if(len == 1) return;
  len >>= 1;
  if(x->apply != -1) {
    impact(x->left, x->apply, len);
    impact(x->right, x->apply, len);
    x->apply = -1;
  }
}
void merge(Node *& x) {
  x->sum = x->left->sum + x->right->sum;
}
void update(Node *& cur, int l, int r, int ql, int qr, int val) {
  if(qr <= l || r <= ql) return;
  if(ql <= l && r <= qr) {
    impact(cur, val, r - l);
    return;
  }
  split(cur, r - l); 
  int mid = (l + r) >> 1;
  update(cur-> left, l, mid, ql, qr, val);
  update(cur->right, mid, r, ql, qr, val);
  merge(cur);
}
void update(Node *& root, int ql, int qr, int val) {
  update(root, 0, N, ql, qr, val);
}
int sum(Node *& cur, int l, int r, int ql, int qr) {
  if(qr <= l || r <= ql) return 0;
  if(ql <= l && r <= qr) {
    return cur->sum;
  }
  split(cur, r - l);
  int mid = (l + r) >> 1;
  return sum(cur->left, l, mid, ql, qr) + sum(cur->right, mid, r, ql, qr);
}
int sum(Node *& root, int ql, int qr) {
  return sum(root, 0, N, ql, qr);
}
// https://codeforces.com/problemset/problem/915/E
void solve(int NT){
  Node *root = new Node();
  int n, q; cin >> n >> q;
  update(root, 0, n, 1); 
  while(q--) {
    int k, x, y; cin >> x >> y >> k; x--; k--;
    update(root, x, y, k);
    cout << sum(root, 0, n) << '\n';
  }
}