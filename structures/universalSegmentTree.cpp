template <typename T, class F = function<T(const T&, const T&)>>
class SegTree{
  public:
    int n,N;
    vector<T> a,tr;
    T NEU; F merge;
    SegTree(const int& sz, const T& neu, const F& func) : n(sz), NEU(neu), merge(func){
      N = (1<<(32-__builtin_clz(n)));
      tr.resize(2*N);
      for(int i = N; i < 2*N; ++i) tr[i] = NEU;
      for(int i = N-1; i > 0; --i) tr[i] = merge(tr[i<<1],tr[i<<1|1]);
    }
    SegTree(const vector<T>& a, const T& neu, const F& func):n(a.size()),NEU(neu),merge(func){
      N = (1<<(32-__builtin_clz(n)));
      tr.resize(2*N);
      for(int i = N; i < 2*N; ++i) tr[i] = (i-N < n ? a[i-N] : NEU);
      for(int i = N-1; i > 0; --i) tr[i] = merge(tr[i<<1],tr[i<<1|1]);
    }
    void set(int idx, const T& val){ 
      for(idx += N, tr[idx] = val, idx >>= 1; idx; idx >>= 1)
        tr[idx] = merge(tr[idx<<1],tr[idx<<1|1]);
    }
    T query(int l, int r){ // [l,r)
      T pref_ans = NEU;
      T suff_ans = NEU;
      for(l += N, r += N; l < r; l >>= 1, r >>= 1){
        if(l&1) pref_ans = merge(pref_ans,tr[l++]);
        if(r&1) suff_ans = merge(tr[--r],suff_ans);
      }
      return merge(pref_ans,suff_ans);
    }
};
// usage:
/*
  SegTree<Node> sg(array, neutral_value, [&](Node a, Node b){
    return func(a,b);
  });
*/