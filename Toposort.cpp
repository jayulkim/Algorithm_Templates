class Toposort {
private:
	using ll = long long;
	ll n;
	vector<vector<ll>>dag;
public:
	Toposort(ll n, const vector<vector<ll>>& dag) {
		this->n = n;
		this->dag = dag;
	}
	pair<bool, vector<ll>> toposort() {
		vector<ll>degree(n + 1, 0);
		for (int i = 1; i <= n; i++) {
			for (auto& j : dag[i]) {
				degree[j]++;
			}
		}
		vector<ll>result;
		queue<ll>q;
		for (int i = 1; i <= n; i++) {
			if (!degree[i]) {
				q.push(i);
			}
		}
		while (!q.empty()) {
			ll temp = q.front();
			q.pop();
			result.push_back(temp);
			for (auto& i : dag[temp]) {
				if (--degree[i] == 0) {
					q.push(i);
				}
			}
		}
		return { result.size() == n, result};
	}
};