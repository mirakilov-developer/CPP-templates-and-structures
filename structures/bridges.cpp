int timer = 0;
vector<vector<pair<int,int>>> g;
vector<int> tin, up, is_bridge; 
void dfs(auto dfs, int x, int u, int id) {
  tin[x] = timer++;
  up[x] = tin[x];
  for(auto [z, idn]: g[x]) {
    if(idn == id) continue;
      if(tin[z] == 0) {
        dfs(dfs, z, x, idn);
        up[x] = min(up[x], up[z]);
    } else {
        up[x] = min(up[x], tin[z]);
    }
  }
  if(u >= 0 && up[x] > tin[u]) {
    is_bridge[id] = 1;
  }
};