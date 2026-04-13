class Fastgcd {
private:
	using ll = long long;
	using ull = unsigned long long;
	using lll = tuple<ll, ll, ll>;
public:
	ull fastgcd(ull a, ull b) {
		ull shift = 0;
		if (a == 0) {
			return b;
		}
		if (b == 0) {
			return a;
		}
		shift = __builtin_ctzll(a | b);
		a >>= __builtin_ctzll(a);
		do {
			b >>= __builtin_ctzll(b);
			if (a > b) {
				swap(a, b);
			}
			b -= a;
		} while (b);
		return a << shift;
	}
	lll eea(ll a, ll mod) {
		ll r1 = a, r2 = mod;
		ll s1 = 1, s2 = 0;
		ll t1 = 0, t2 = 1;
		while (r2) {
			ll q = r1 / r2;
			ll r = r1 - q * r2;
			r1 = r2;
			r2 = r;
			ll s = s1 - q * s2;
			s1 = s2;
			s2 = s;
			ll t = t1 - q * t2;
			t1 = t2;
			t2 = t;
		}
		return { r1, s1, t1 };
	}
};