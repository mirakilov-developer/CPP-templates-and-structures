struct two_sat {
  int n, N;
  vector<vector<int>> edges, rev;
  vector<int> used, comp, topsort;
  two_sat(int sz):n(sz) {
    N = 2 * sz;
    edges.resize(N); rev.resize(N);
    used.resize(N); comp.assign(N, -1);
    topsort.reserve(sz);
  }
  void addEdge(int v, int u) {
    edges[v].push_back(u);
    rev[u].push_back(v);
  }
  void dfs1(int v) {
    used[v] = 1;
    for(int u : edges[v]) if(!used[u]) dfs1(u);
    topsort.emplace_back(v);
  }
  void dfs2(int v, int clr) {
    comp[v] = clr;
    for(int u : rev[v]) {
      if(comp[u] == -1) dfs2(u, clr);
    }
  }
  void add_implication(int v, int u) {
    addEdge(v, u);
    addEdge(u ^ 1, v ^ 1);
  }
  // ... or (v and u) or ...
  // 2 * x -> v, 2 * x + 1 -> not v
  // x is zero indexed
  void add_or(int v, int u) {
    add_implication(v ^ 1, u);
  }
  // all or's are added
  bool solver(vector<int>& ans) {
    for(int v = 0; v < N; ++v) {
      if(!used[v]) dfs1(v);
    }
    reverse(all(topsort));
    int clr = 0;
    for(int v: topsort) {
      if(comp[v] == -1) dfs2(v, clr++);
    }
    for(int v = 0; v < N; ++v) {
      if(comp[v] == comp[v ^ 1]) return false;
    }
    for(int v = 0; v < n; ++v) {
      ans[v] = comp[v << 1] > comp[v << 1 | 1];
    }
    return true;
  }
};
