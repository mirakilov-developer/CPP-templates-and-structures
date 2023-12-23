vector<int> sz, used;
vector<vector<int>> g;
int get_centroid(int root) {
    auto sub_size = [&](auto sub_size, int x, int p) -> void {
        sz[x] = 1;
        for(int z: g[x]) {
            if(z != p && used[z] == 0) {
                sub_size(sub_size, z, x);
                sz[x] += sz[z];
            }
        }
    };
    sub_size(sub_size, root, -1);
    int n = sz[root];
    auto dfs = [&](auto dfs, int x, int p) -> int {
        for(int z: g[x]) {
            if(z != p && used[z] == 0) {
                if(2 * sz[z] >= n) return dfs(dfs, z, x);
            }
        }
        return x;
    };
    return dfs(dfs, root, -1);
}

// count all paths of length k
// call get(root)
long long get(int cur) {
    int x = get_centroid(cur);
    long long ans = 0;
    
    vector<int> v(sz[x] + 1); v[0]++;
    auto dfs = [&](auto dfs, int x, int p, int dep, vector<int>& cnt) -> void {
        if(k >= dep && k - dep < v.size()) ans += v[k - dep];
        cnt.emplace_back(dep);

        for(int z: g[x]) {
            if(z != p && used[z] == 0) {
                dfs(dfs, z, x, dep + 1, cnt);
            }
        }
    };

    used[x] = 1;
    for(int z: g[x]) {
        if(used[z] == 0) {
            vector<int> c;
            dfs(dfs, z, x, 1, c);
            for(int val: c) v[val]++;
            
            ans += get(z);
        }
    }

    return ans;
}