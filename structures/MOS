// MO'S ALGORITHM (array only). Version 1.0 
// PROCESS OFFLINE QUERIES IN O((n+m)*sqrt(n))
// DQUERY VERSION (count distinct numbers in range)
// Change only Range_Handler (and int,ll and etc.)
// **NOTE WORK WITH [l,r)
struct MO{
    
    struct Query{
        int l,r,id;
    };
    
    struct Range_Handler{ // the structure to handle queries on range
        vector<int> a;
        
        int ans = 0;
        Range_Handler(int upper_range){
            a.assign(upper_range+1,0);
        }
        
        // remove from range
        void rem(int x){
            a[x]--;
            if(a[x] == 0) ans--;
        }
        
        // add to range
        void add(int x){
            a[x]++;
            if(a[x] == 1) ans++;
        }
        
        // get ans in this range
        int get_ans(){
            return ans;
        }
    };
    
    // main code
    // call as, get(arr, queries, extra)
    vector<int> get(vector<int> &arr, vector<pii> &initial, int extra = 0){
        int n = initial.size();
        int BS = sqrt(n);
        
        vector<Query> qs;
        for(int i = 0; i < n; ++i){
            qs.pb({initial[i].fi,initial[i].se,i});
        }
        
        sort(all(qs),[&](const Query &a, const Query &b)->bool{
            return (a.l/BS < b.l/BS) || (a.l/BS == b.l/BS && a.r < b.r);
        });
        
        vector<int> ans(n);
        Range_Handler observer(extra);
        
        int l = 0, r = 0;
        for(int i = 0; i < n; ++i){
            int x = qs[i].l, y = qs[i].r;
            
            while(r < y) observer.add(arr[r++]);
            while(l < x) observer.rem(arr[l++]);
            while(l > x) observer.add(arr[--l]);
            while(r > y) observer.rem(arr[--r]);
            
            ans[qs[i].id] = observer.get_ans();
        }
        
        return ans;
    }
    
} query_manager;