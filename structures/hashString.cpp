struct HashedString {
	// change M and B if you want
  // 1000000007, 1000000009, 1000000021
	static const ll M = (1LL << 61) - 1;
	static const ll B;
	static __int128 mul(ll a, ll b) { return (__int128)a * b; }
	static ll mod_mul(ll a, ll b) { return mul(a, b) % M; }
	// pow[i] contains P^i % M
	static vector<ll> pow;
	// p_hash[i] is the hash of the first i characters of the given string
	vector<ll> p_hash;
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) {
      pow.push_back(mod_mul(pow.back(), B));
    }
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M;
		}
	}
	ll getHash(int l, int r) { // [l, r)
		ll raw_val = p_hash[r] - mod_mul(p_hash[l], pow[r - l]);
		return (raw_val + M) % M;
	}
};
mt19937 rng((uint32_t)chrono::steady_clock:: now().time_since_epoch().count());
vector<ll> HashedString::pow = {1};
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);
const auto M = HashedString::M;
const auto B = HashedString::B;
const auto mul = HashedString::mul;
const auto mod_mul = HashedString::mod_mul;
// usage: HashedString hs(h)