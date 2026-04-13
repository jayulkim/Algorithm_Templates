class Fastmod {
private:
	using ll = long long;
	using ull = unsigned long long;
	ull mod;
	ull norm(ll x) {
		ll m = (ll)mod;
		x %= m;
		if (x < 0) x += m;
		return (ull)x;
	}
	ull addmod_u(ull a, ull b) {
		if (a >= mod - b) {
			return a - (mod - b);
		}
		return a + b;
	}
public:
	Fastmod(ull mod) {
		this->mod = mod;
	}
	ull addmod(ull a, ull b) {
		return addmod_u(a, b);
	}
	ull addmod(ll a, ll b) {
		return addmod_u(norm(a), norm(b));
	}
	ull fastmulmod(ull a, ull b) {
		long long result = a * b - mod * (ull)(1.L / mod * a * b);
		if (result < 0) {
			result += mod;
		}
		if ((ull)result >= mod) {
			result -= mod;
		}
		return (ull)result;
	}
	ull fastmulmod(ll a, ll b) {
		return fastmulmod(norm(a), norm(b));
	}
	ull mulmod(ull a, ull b) {
		ull result = 0;
		while (b) {
			if (b & 1) {
				result = addmod_u(result, a);
			}
			a = addmod_u(a, a);
			b >>= 1;
		}
		return result;
	}
	ull mulmod(ll a, ll b) {
		return mulmod(norm(a), norm(b));
	}
	ull fastpowmod(ll a, ull b) {
		ull x = norm(a);
		ull result = 1;
		while (b) {
			if (b & 1) {
				result = fastmulmod(result, x);
			}
			x = fastmulmod(x, x);
			b >>= 1;
		}
		return result;
	}
	ull powmod(ll a, ull b) {
		ull x = norm(a);
		ull result = 1;
		while (b) {
			if (b & 1) {
				result = mulmod(result, x);
			}
			x = mulmod(x, x);
			b >>= 1;
		}
		return result;
	}
};