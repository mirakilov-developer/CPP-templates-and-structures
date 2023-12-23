struct AHO {
  struct vertex {
    int next[26], go[26];
    int p, pch, link;
    bool leaf;
  };
  int n,sz;
  vector<vertex> t;
  // size = sum of strings
  AHO(int size):n(size) {
    t.resize(size);
    t[0].p = t[0].link = -1;
    memset(t[0].next, -1, sizeof t[0].next);
    memset(t[0].go, -1, sizeof t[0].go);
    sz = 1;
  }
  void addString(string s) {
    int v = 0;
    for (auto x : s) {
      x -= 'a';
      if (t[v].next[x] == -1) {
        memset(t[sz].next, -1, sizeof t[sz].next);
        memset(t[sz].go, -1, sizeof t[sz].go);
        t[sz].p = v;
        t[sz].link = -1;
        t[sz].pch = x;
        t[v].next[x] = sz++;
      }
      v = t[v].next[x];
    }
    t[v].leaf = true;
  }
  int getLink(int v) {
    if (t[v].link == -1) {
      if (v == 0 || t[v].p == 0)
          t[v].link = 0;
      else
          t[v].link = go(getLink(t[v].p), t[v].pch);
    }
    return t[v].link;
  }
  int go(int v, int c) {
    if (t[v].go[c] == -1) {
      if (t[v].next[c] != -1)
          t[v].go[c] = t[v].next[c];
      else
          t[v].go[c] = v == 0 ? 0 : go(getLink(v), c);
    }
    return t[v].go[c];
  }
};