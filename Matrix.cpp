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
class Matrix {
private:
	using ll = long long;
	using ull = unsigned long long;
	using matrix = vector<vector<ll>>;
	using matrix_u = vector<vector<ull>>;
	ull mod;
	Fastmod fm;
public:
	Matrix(ull mod) : mod(mod), fm(mod) {}
	ll pow(ll a, ull b) {
		ll result = 1;
		while (b) {
			if (b & 1) {
				result *= a;
			}
			a *= a;
			b >>= 1;
		}
		return result;
	}
	ull pow(ull a, ull b) {
		ull result = 1;
		while (b) {
			if (b & 1) {
				result *= a;
			}
			a *= a;
			b >>= 1;
		}
		return result;
	}
	matrix addmod(const matrix& a, const matrix& b) {
		ll n = a.size();
		ll m = a[0].size();
		if (n != (ll)b.size() || m != (ll)b[0].size()) {
			return { {} };
		}
		matrix result = a;
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < m; j++) {
				result[i][j] = fm.addmod(result[i][j], b[i][j]);
			}
		}
		return result;
	}
	matrix_u addmod(const matrix_u& a, const matrix_u& b) {
		ll n = a.size();
		ll m = a[0].size();
		if (n != (ll)b.size() || m != (ll)b[0].size()) {
			return { {} };
		}
		matrix_u result = a;
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < m; j++) {
				result[i][j] = fm.addmod(result[i][j], b[i][j]);
			}
		}
		return result;
	}
	matrix mulmod(const matrix& a, const matrix& b) {
		if ((ll)a[0].size() != (ll)b.size()) {
			return { {} };
		}
		matrix result(a.size(), vector<ll>(b[0].size(), 0));
		for (ll i = 0; i < (ll)a.size(); i++) {
			for (ll k = 0; k < (ll)a[0].size(); k++) {
				if (a[i][k]) {
					for (ll j = 0; j < (ll)b[0].size(); j++) {
						result[i][j] = fm.addmod(result[i][j], (ll)fm.fastmulmod(a[i][k], b[k][j]));
					}
				}
			}
		}
		return result;
	}
	matrix mul(const matrix& a, const matrix& b) {
		if ((ll)a[0].size() != (ll)b.size()) {
			return { {} };
		}
		matrix result(a.size(), vector<ll>(b[0].size(), 0));
		for (ll i = 0; i < (ll)a.size(); i++) {
			for (ll k = 0; k < (ll)a[0].size(); k++) {
				if (a[i][k]) {
					for (ll j = 0; j < (ll)b[0].size(); j++) {
						result[i][j] += a[i][k] * b[k][j];
					}
				}
			}
		}
		return result;
	}
	matrix_u mulmod(const matrix_u& a, const matrix_u& b) {
		if (a[0].size() != b.size()) {
			return { {} };
		}
		matrix_u result(a.size(), vector<ull>(b[0].size(), 0));
		for (ll i = 0; i < (ll)a.size(); i++) {
			for (ll k = 0; k < (ll)a[0].size(); k++) {
				if (a[i][k]) {
					for (ll j = 0; j < (ll)b[0].size(); j++) {
						result[i][j] = fm.addmod(result[i][j], fm.fastmulmod(a[i][k], b[k][j]));
					}
				}
			}
		}
		return result;
	}
	matrix_u mul(const matrix_u& a, const matrix_u& b) {
		if (a[0].size() != b.size()) {
			return { {} };
		}
		matrix_u result(a.size(), vector<ull>(b[0].size(), 0));
		for (ll i = 0; i < (ll)a.size(); i++) {
			for (ll k = 0; k < (ll)a[0].size(); k++) {
				if (a[i][k]) {
					for (ll j = 0; j < (ll)b[0].size(); j++) {
						result[i][j] += a[i][k] * b[k][j];
					}
				}
			}
		}
		return result;
	}
	matrix identity(ll n) {
		matrix result(n, vector<ll>(n, 0));
		for (ll i = 0; i < n; i++) {
			result[i][i] = 1;
		}
		return result;
	}
	matrix powmod(matrix a, ull b) {
		if (a.size() != a[0].size()) {
			return { {} };
		}
		matrix result = identity((ll)a.size());
		while (b) {
			if (b & 1) {
				result = mulmod(result, a);
			}
			a = mulmod(a, a);
			b >>= 1;
		}
		return result;
	}
	matrix pow(matrix a, ull b) {
		if (a.size() != a[0].size()) {
			return { {} };
		}
		matrix result = identity((ll)a.size());
		while (b) {
			if (b & 1) {
				result = mul(result, a);
			}
			a = mul(a, a);
			b >>= 1;
		}
		return result;
	}
	matrix_u identity(ull n) {
		matrix_u result(n, vector<ull>(n, 0));
		for (ull i = 0; i < n; i++) {
			result[i][i] = 1;
		}
		return result;
	}
	matrix_u powmod(matrix_u a, ull b) {
		if (a.size() != a[0].size()) {
			return { {} };
		}
		matrix_u result = identity((ull)a.size());
		while (b) {
			if (b & 1) {
				result = mulmod(result, a);
			}
			a = mulmod(a, a);
			b >>= 1;
		}
		return result;
	}
	matrix_u pow(matrix_u a, ull b) {
		if (a.size() != a[0].size()) {
			return { {} };
		}
		matrix_u result = identity((ull)a.size());
		while (b) {
			if (b & 1) {
				result = mul(result, a);
			}
			a = mul(a, a);
			b >>= 1;
		}
		return result;
	}
};