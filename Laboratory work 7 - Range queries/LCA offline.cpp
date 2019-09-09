#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector < vector < pair<int, int> > > arr;
vector <int> h, p, sz, ans;
vector < pair<int, int> > minu;
vector <bool> used;

void set_h(int v, int par, int ht) {
	h[v] = ht;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == par)
			continue;
		set_h(to, v, ht + 1);
	}
}

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

	if (sz[v] < sz[u])
		swap(v, u);

	p[u] = v;
	sz[v] += sz[u];
	minu[v] = min(minu[v], minu[u]);
}

void dfs(int v, int par) {
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (used[to])
			continue;
		dfs(to, v);
	}
	while (!arr[v].empty()) {
		if (used[arr[v].back().first])
			ans[arr[v].back().second] = minu[get(arr[v].back().first)].second;
		arr[v].pop_back();
	}
	join(v, par);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int q, n = 1, a, b;
	cin >> q;

	vector < pair<int, int> > ask;
	vector < pair<int, int> > edge;

	string s;

	while (q--) {
		cin >> s >> a >> b;
		if (s == "ADD") {
			n = max(n, max(a, b));
			edge.push_back(make_pair(a - 1, b - 1));
		} else {
			ask.push_back(make_pair(a - 1, b - 1));
		}
	}

	g.resize(n);
	arr.resize(n);
	used.resize(n);
	h.resize(n);

	for (int i = 0; i < (int)edge.size(); i++) {
		g[edge[i].first].push_back(edge[i].second);
		g[edge[i].second].push_back(edge[i].first);
	}

	for (int i = 0; i < (int)ask.size(); i++) {
		arr[ask[i].first].push_back(make_pair(ask[i].second, i));
		arr[ask[i].second].push_back(make_pair(ask[i].first, i));
	}

	set_h(0, 0, 0);

	p.resize(n);
	sz.resize(n, 1);
	minu.resize(n);

	for (int i = 0; i < n; i++) {
		p[i] = i;
		minu[i] = make_pair(h[i], i);
	}

	ans.resize((int)ask.size());
	dfs(0, 0);

	for (int i = 0; i < (int)ans.size(); i++)
		cout << ans[i] + 1 << '\n';

	return 0;
}
