#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

struct edge {
	int to, f, c, cost;

	edge() = default;

	edge(int nt, int fn, int cn, int ccn) {
		to = nt;
		f = fn;
		c = cn;
		cost = ccn;
	}
};

int s, t;
vector < vector<int> > g;
vector <edge> lst;

bool push_flow() {
	vector <int> d(g.size(), inf);
	vector < pair<int, int> > par(g.size(), make_pair(-1, -1));
	d[s] = 0;

	for (int t = 0; t < (int)g.size(); t++) {
		bool any = false;
		for (int i = 0; i < (int)g.size(); i++) {
			if (d[i] == inf)
				continue;
			for (int j = 0; j < (int)g[i].size(); j++) {
				int num = g[i][j];
				if (lst[num].f == lst[num].c)
					continue;
				if (d[lst[num].to] > d[i] + lst[num].cost) {
					any = true;
					d[lst[num].to] = d[i] + lst[num].cost;
					par[lst[num].to] = make_pair(i, num);
				}
			}
		}
		if (!any)
			break;
	}

	int add = inf;
	pair <int, int> cur = make_pair(t, -1);
	vector <int> path;
	while (true) {
		if (cur.second != -1) {
			path.push_back(cur.second);
			add = min(add, lst[cur.second].c - lst[cur.second].f);
		}
		if (par[cur.first].first == -1)
			break;
		cur = par[cur.first];
	}
	for (int i = 0; i < (int)path.size(); i++) {
		lst[path[i]].f += add;
		lst[path[i] ^ 1].f -= add;
	}
	return (!path.empty());
}


vector < vector< pair<int, bool> > > gm;
vector <int> match, ans;
vector <bool> used;

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < (int)gm[v].size(); i++) {
		if (!gm[v][i].second)
			continue;
		int to = gm[v][i].first;
		if (match[to] == -1 || dfs(match[to])) {
			match[to] = v;
			return true;
		}
	}
	return false;
}

inline void kuhn(int n) {
	for (int i = 0; i < n; i++)
		match[i] = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i);
	}
	for (int i = 0; i < n; i++)
		ans[match[i]] = i;
	for (int i = 0; i < n; i++)
		cout << ans[i] + 1 << ' ';
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, a, b, cost, numeric = 0;
	cin >> n >> k;

	s = 0; t = 2 * n + 1;

	g.resize(2 * n + 2);
	lst.resize(2 * (n * n + 2 * n));

	for (int i = 0; i < n; i++) {
		lst[numeric] = edge(i + 1, 0, k, 0);
		g[s].push_back(numeric++);
		lst[numeric] = edge(s, 0, 0, 0);
		g[i + 1].push_back(numeric++);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a = i + 1; b = j + 1 + n;
			cin >> cost;
			lst[numeric] = edge(b, 0, 1, cost);
			g[a].push_back(numeric++);
			lst[numeric] = edge(a, 0, 0, -cost);
			g[b].push_back(numeric++);
		}
	}
	for (int i = 0; i < n; i++) {
		lst[numeric] = edge(t, 0, k, 0);
		g[i + 1 + n].push_back(numeric++);
		lst[numeric] = edge(i + 1 + n, 0, 0, 0);
		g[t].push_back(numeric++);
	}

	while (push_flow()) {}

	long long sum = 0ll;
	for (int i = 0; i < (int)lst.size(); i += 2)
		sum += (long long)lst[i].f * (long long)lst[i].cost;
	cout << sum << '\n';

	gm.resize(n);
	match.resize(n);
	used.resize(n);
	ans.resize(n);

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			int num = g[i][j];
			if (lst[num].f == 1) {
				gm[i - 1].push_back(make_pair(lst[num].to - n - 1, true));
			}
		}
	}

	for (int t = 0; t < k; t++) {
		kuhn(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < (int)gm[i].size(); j++) {
				if (ans[i] == gm[i][j].first)
					gm[i][j].second = false;
			}
		}
	}
    return 0;
}
