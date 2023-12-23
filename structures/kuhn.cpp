vector<vector<int>> g;
vector<int> vis, mt;

bool kuhn(int x) {
  if(vis[x]) return false;
  vis[x] = true;
  for(int z: g[x]) {
    if(mt[z] == -1 || kuhn(mt[z])) {
      mt[z] = x;
      return true;
    }
  }
  return false;
}

// n -> left part. Numbered from 1 .. n
// m -> right part. Numbered from 1 .. ,
void solve(int NT){
  int n, m; cin >> n >> m;
  
  g.resize(n + m + 1);
  mt.assign(m + 1, -1);

  // reading graph
  for(int i = 1, x; i <= n; ++i) {
    while(cin >> x) {
      if(x == 0) break;
      g[i].emplace_back(x);
    }
  }

  for(int i = 1; i <= n; ++i) {
    vis.assign(n + 1, 0);
    kuhn(i);
  }

  cout << m - count(mt.begin() + 1, mt.end(), -1) << '\n';
  for(int i = 1; i <= m; ++i) {
    if(mt[i] != -1) {
      cout << mt[i] << ' ' << i << '\n';
    }
  }
}