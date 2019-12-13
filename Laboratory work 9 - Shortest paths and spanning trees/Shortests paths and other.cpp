#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = (ll)9e+18;

vector < vector< pair<int, ll> > > g;
vector <ll> d;
vector <int> color;
vector <bool> cycle;

void dfs(int v) {
	cycle[v] = true;
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, s;
	cin >> n >> m >> s;
	s--;

	g.resize(n);
	d.resize(n, inf);
	color.resize(n);
	cycle.resize(n);

	int a, b;
	ll c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a - 1].push_back(make_pair(b - 1, c));
	}

	d[s] = 0ll;
	for (int t = 0; t < n; t++) {
		vector <ll> upd(n, inf);
		for (int i = 0; i < n; i++) {
			if (d[i] == inf)
				continue;
			for (int j = 0; j < (int)g[i].size(); j++) {
				int to = g[i][j].first;
				ll edge = g[i][j].second;
				if (d[to] > d[i] + edge) {
					upd[to] = d[i] + edge;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (upd[i] != inf)
				d[i] = upd[i];
		}
	}
	for (int i = 0; i < n; i++) {
		if (d[i] == inf)
			continue;
		for (int j = 0; j < (int)g[i].size(); j++) {
			int to = g[i][j].first;
			ll edge = g[i][j].second;
			if (d[to] > d[i] + edge && color[to] == 0)
				dfs(to);
		}
	}

	for (int i = 0; i < n; i++) {
		if (cycle[i]) {
			cout << "-\n";
		} else {
			if (d[i] == inf) {
				cout << "*\n";
			} else {
				cout << d[i] << '\n';
			}
		}
	}

	return 0;
}
