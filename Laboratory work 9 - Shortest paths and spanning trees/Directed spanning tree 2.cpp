#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector < set < pair<ll, int> > > g;
vector <ll> lazy;
vector <int> p;

int get(int v) {
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u)
		return;
	if ((int)g[v].size() < (int)g[u].size())
		swap(v, u);
	while (!g[u].empty()) {
		if (get(g[u].begin()->second) != v)
			g[v].insert(make_pair(g[u].begin()->first + lazy[u] - lazy[v], g[u].begin()->second));
		g[u].erase(g[u].begin());
	}
	p[u] = v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
	cin >> n >> m;

	g.resize(n);
	p.resize(n);
	lazy.resize(n);

	int a, b;
	ll c;

	vector < vector <int> > gg(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (b == 1 || a == b)
			continue;
		g[b - 1].insert(make_pair(c, a - 1));
		gg[a - 1].push_back(b - 1);
	}

	vector <int> d(n, n + 1);
	d[0] = 0;
	queue <int> q;
	q.push(0);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < (int)gg[v].size(); i++) {
			int to = gg[v][i];
			if (d[to] > d[v] + 1) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}

	bool flag = true;
	for (int i = 0; i < n; i++)
		flag &= (d[i] != n + 1);

	if (!flag) {
		cout << "NO";
		return 0;
	}

	cout << "YES\n";

	ll ans = 0ll;

	for (int i = 0; i < n; i++) {
		p[i] = i;
	}

	vector <bool> used(n);
	vector <int> prev(n);

	for (int i = 0; i < n; i++) {
		int v = get(i);
		prev[v] = -1;
		while (v != get(0)) {
			used[v] = true;
			while (!g[v].empty() && get(g[v].begin()->second) == v) {
				g[v].erase(g[v].begin());
			}
			ll cur = g[v].begin()->first + lazy[v];
			lazy[v] -= cur;
			int to = get(g[v].begin()->second);
			ans += cur;
			if (to == get(0)) {
				int u = v;
				while (u != -1) {
					join(u, 0);
					u = prev[u];
				}
				break;
			}
			if (used[to]) {
				vector <int> path;
				int u = v;
				while (true) {
					path.push_back(u);
					if (u == to)
						break;
					u = prev[u];
				}
				int root = prev[to];
				for (int j = 1; j < (int)path.size(); j++)
					join(path[j - 1], path[j]);
				prev[get(to)] = root;
				v = get(v);
				continue;
			}
			prev[to] = v;
			v = to;
		}
	}
	cout << ans;
	return 0;
}
