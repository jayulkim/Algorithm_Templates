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
	Fastmod(ull mod) : mod(mod) {}
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
	ull divmod(ll up, ll down) {
		return fastmulmod(norm(up), fastpowmod(norm(down), mod - 2));
	}
};
class Primecheck {
private:
	using ull = unsigned long long;
public:
	bool bigisprime(ull x) {
		static const ull sample[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
		if (x < 2 || x % 6 % 4 != 1) {
			return (x | 1) == 3;
		}
		Fastmod fm(x);
		ull s = __builtin_ctzll(x - 1);
		ull d = (x - 1) >> s;
		for (ull a : sample) {
			ull temp = fm.fastpowmod(a % x, d);
			ull i = s;
			while (temp != 1 && temp != x - 1 && a % x && i--) {
				temp = fm.fastmulmod(temp, temp);
			}
			if (temp != x - 1 && i != s) {
				return false;
			}
		}
		return true;
	}
	bool isprime(ull x) {
		if (x < 2) {
			return false;
		}
		if (x % 2 == 0) {
			return x == 2;
		}
		for (ull i = 3; i <= x / i; i += 2) {
			if (x % i == 0) {
				return false;
			}
		}
		return true;
	}
	vector<bool> eratosthenes(ull n) {
		vector<bool>result(n + 1, false);
		result[1] = true;
		for (int i = 2; i * i <= n; i++) {
			if (!result[i]) {
				for (int j = i * i; j <= n; j += i) {
					result[j] = true;
				}
			}
		}
		return result;
	}
};