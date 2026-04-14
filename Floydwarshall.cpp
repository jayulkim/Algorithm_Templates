class Floydwarshall {
private:
	using ll = long long;
	ll n;
	vector<vector<ll>>graph;
public:
	Floydwarshall(ll n, const vector<vector<ll>>& graph) : n(n), graph(graph) {}
	vector<vector<ll>> run() {
		vector<vector<ll>>dist = graph;
		for (int i = 1; i <= n; i++) {
			dist[i][i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					if (dist[j][i] != LLONG_MAX && dist[i][k] != LLONG_MAX) {
						dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
					}
				}
			}
		}
		return dist;
	}
	pair<vector<vector<ll>>, vector<vector<ll>>>revrun() {
		vector<vector<ll>>dist = graph;
		vector<vector<ll>>next(n + 1, vector<ll>(n + 1, -1));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (graph[i][j] != LLONG_MAX) {
					next[i][j] = j;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			dist[i][i] = 0;
			next[i][i] = i;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = 1; k <= n; k++) {
					if (dist[j][i] != LLONG_MAX && dist[i][k] != LLONG_MAX) {
						ll temp = dist[j][i] + dist[i][k];
						if (temp < dist[j][k]) {
							dist[j][k] = temp;
							next[j][k] = next[j][i];
						}
					}
				}
			}
		}
		return { dist, next };
	}
	vector<ll> getpath(ll start, ll end, const vector<vector<ll>>& next) {
		if (next[start][end] == -1) {
			return {};
		}
		vector<ll>path = { start };
		for (int i = 0; i <= n; i++) {
			if (start == end) {
				return path;
			}
			start = next[start][end];
			path.push_back(start);
		}
		return {};
	}
};