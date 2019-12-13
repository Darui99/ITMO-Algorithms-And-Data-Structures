#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = (ll)1e+18 + 7ll;

vector < vector < pair<int, ll> > > g;
vector < vector<bool> > can;
vector<int> par, color, comp, cycle;
stack <int> q;

void roadroller(int n) {
	can.clear();
	can.resize(n);
	par.clear();
	par.resize(n, -1);
	color.clear();
	color.resize(n);
	comp.clear();
	comp.resize(n, -1);
	cycle.clear();
	cycle.resize(n);
}

void dfs(int v, int p) {
	q.push(v);
	color[v] = 1;
	par[v] = p;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (!can[v][i])
			continue;
		if (color[to] == 1) {
			int cur = v;
			while (true) {
				cycle[cur] = true;
				if (cur == to)
					break;
				cur = par[cur];
			}
		}
		if (color[to] == 0)
			dfs(to, v);
	}
	color[v] = 2;
}

ll solve() {
	ll res = 0ll;
	int n = (int)g.size();
	if (n == 1)
		return 0ll;
	roadroller(n);
	vector <ll> minu(n, inf);
	vector < pair<int, int> > iminu(n, make_pair(-1, 1));
	for (int i = 0; i < n; i++) {
		can[i].resize(g[i].size());
		for (int j = 0; j < (int)g[i].size(); j++) {
			int to = g[i][j].first;
			ll edge = g[i][j].second;
			if (minu[to] > edge) {
				minu[to] = edge;
				iminu[to] = make_pair(i, j);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (minu[i] != inf) {
			res += minu[i];
			can[iminu[i].first][iminu[i].second] = true;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			g[i][j].second -= minu[g[i][j].first];
		}
	}
	int cur_comp = 0;
	stack <int> cycq;
	bool was_cycle = false;
	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			dfs(i, -1);
			while (!q.empty()) {
				if (cycle[q.top()]) {
					cycq.push(q.top());
				} else {
					comp[q.top()] = cur_comp++;
				}
				q.pop();
			}
			if (!cycq.empty()) {
				was_cycle = true;
				cur_comp++;
			}
			while (!cycq.empty()) {
				comp[cycq.top()] = cur_comp - 1;
				cycq.pop();
			}
		}
	}
	if (!was_cycle)
		return res;
	vector < vector < pair<int, ll> > > ng(cur_comp);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			int to = g[i][j].first;
			if (comp[i] == comp[to])
				continue;
			ll edge = g[i][j].second;
			ng[comp[i]].push_back(make_pair(comp[to], edge));
		}
	}
	g.swap(ng);
	return res + solve();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	g.resize(n);

	int a, b;
	ll c;

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		if (b == 1 || a == b)
			continue;
		g[a - 1].push_back(make_pair(b - 1, c));
	}

	vector <int> d(n, n + 1);
	d[0] = 0;
	queue <int> q;
	q.push(0);

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = g[v][i].first;
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
	cout << solve();

	return 0;
}
