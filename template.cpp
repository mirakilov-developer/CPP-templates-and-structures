struct DSU {
    vector<int> p,r;
    
    DSU(int n) {
        p.resize(n); iota(p.begin(), p.end(), 0);
        r.assign(n, 1);
    }

    int get(int x) {
        return p[x] = (p[x] == x ? x : get(p[x]));
    }

    void unite(int a, int b) {
        a = get(a); b = get(b);
        if(b == a) return;
        if(r[a] > r[b]) swap(a, b);
        r[b] += r[a]; p[a] = b; r[a] = 0;
    }

    int get_size(int x) {
        return r[get(x)];
    }
};