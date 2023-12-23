// 0-indexed
struct Fenwick {
  int n;
  vector<ll> ft;
  Fenwick(int n) : n(n) { ft.resize(n); }
  ll sum(int r) {
    ll result = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      result += ft[r];
    return result;
  }
  ll sum(int l, int r) { // [l, r]
    return (l > r ? 0ll : sum(r) - sum(l - 1));
  }
  void inc(int i, ll delta) {
    for (; i < n; i = (i | (i + 1)))
      ft[i] += delta;
  }
};
struct Fenwick2d {
  int n, m;
  vector<vector<ll>> ft;
  Fenwick2d(int n, int m) : n(n), m(m) {
    ft.assign(n, vector<ll>(m));
  }
  // [xxxx.] 
  // [xxxp.] p -> (x, y)
  // [.....] 
  ll sum(int x, int y) {
    ll result = 0;
    for (int i = x; i >= 0; i = (i & (i+1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j+1)) - 1) {
        result += ft[i][j];
      }
    }
    return result;
  }
  void inc(int x, int y, ll delta) {
    for (int i = x; i < n; i = (i | (i+1))) {
      for (int j = y; j < m; j = (j | (j+1))) {
        ft[i][j] += delta;
      }
    }
  }
};