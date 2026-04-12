class Dijkstra {
private:
	using ll = long long;
	using pll = pair<ll, ll>;
	ll n;
	vector<ll>start;
	vector<vector<pll>>graph;
public:
	vector<ll>dist;
	vector<vector<pll>>revgraph;
	Dijkstra(ll n, vector<ll>start, vector<vector<pll>>&graph) {
		this->n = n;
		this->start = start;
		this->graph = graph;
	}
	vector<ll> run() {
		priority_queue<pll, vector<pll>, greater<pll>>pq;
		dist.assign(n + 1, LLONG_MAX);
		for (auto& i : start) {
			dist[i] = 0;
			pq.push({ 0, i });
		}
		while (!pq.empty()) {
			auto [a, b] = pq.top();
			pq.pop();
			if (dist[b] >= a) {
				for (auto& i : graph[b]) {
					if (dist[i.first] > dist[b] + i.second) {
						dist[i.first] = dist[b] + i.second;
						pq.push({ dist[i.first], i.first });
					}
				}
			}
		}
		return dist;
	}
	pair<vector<ll>, vector<vector<pll>>> revrun() {
		priority_queue<pll, vector<pll>, greater<pll>>pq;
		dist.assign(n + 1, LLONG_MAX);
		revgraph.assign(n + 1, vector<pll>());
		for (auto& i : start) {
			dist[i] = 0;
			pq.push({ 0, i });
		}
		while (!pq.empty()) {
			auto [a, b] = pq.top();
			pq.pop();
			if (dist[b] >= a) {
				for (auto& i : graph[b]) {
					if (dist[i.first] > dist[b] + i.second) {
						vector<pll>().swap(revgraph[i.first]);
						revgraph[i.first].push_back({ b, i.second });
						dist[i.first] = dist[b] + i.second;
						pq.push({ dist[i.first], i.first });
					}
					else if (dist[i.first] == dist[b] + i.second) {
						revgraph[i.first].push_back({ b, i.second });
					}
				}
			}
		}
		return { dist, revgraph };
	}
};