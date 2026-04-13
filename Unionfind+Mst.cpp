class Unionfind {
private:
	using ll = long long;
	using pll = pair<ll, ll>;
	using lll = tuple<ll, ll, ll>;
	ll n;
	vector<ll>parent;
	vector<ll>rank;
public:
	void init() {
		parent.resize(n + 1);
		iota(parent.begin(), parent.end(), 0);
		rank.assign(n + 1, 1);
	}
	Unionfind(ll n) : n(n) {
		init();
	}
	ll getparent(ll x) {
		if (x == parent[x]) {
			return x;
		}
		return parent[x] = getparent(parent[x]);
	}
	void merge(ll a, ll b) {
		a = getparent(a);
		b = getparent(b);
		if (a == b) {
			return;
		}
		if (rank[a] > rank[b]) {
			rank[a] += rank[b];
			rank[b] = 0;
			parent[b] = a;
		}
		else {
			rank[b] += rank[a];
			rank[a] = 0;
			parent[a] = b;
		}
	}
	ll minkruskal(priority_queue<lll, vector<lll>, greater<lll>>& pq) {
		init();
		ll result = 0;
		ll count = 0;
		while (!pq.empty() && count < n - 1) {
			auto [a, b, c] = pq.top();
			pq.pop();
			if (getparent(b) != getparent(c)) {
				count++;
				result += a;
				merge(b, c);
			}
		}
		return (count == n - 1 ? result : LLONG_MAX);
	}
	ll maxkruskal(priority_queue<lll>& pq) {
		init();
		ll result = 0;
		ll count = 0;
		while (!pq.empty() && count < n - 1) {
			auto [a, b, c] = pq.top();
			pq.pop();
			if (getparent(b) != getparent(c)) {
				count++;
				result += a;
				merge(b, c);
			}
		}
		return (count == n - 1 ? result : LLONG_MAX);
	}
	bool hascycle(const vector<vector<ll>>& graph) {
		init();
		for (int i = 1; i <= n; i++) {
			for (auto& j : graph[i]) {
				if (i < j) {
					if (getparent(i) == getparent(j)) {
						return true;
					}
					merge(i, j);
				}
			}
		}
		return false;
	}
	bool hascycle(const vector<vector<pll>>& graph) {
		init();
		for (int i = 1; i <= n; i++) {
			for (auto& j : graph[i]) {
				if (i < j.first) {
					if (getparent(i) == getparent(j.first)) {
						return true;
					}
					merge(i, j.first);
				}
			}
		}
		return false;
	}
};