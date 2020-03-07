#include <bits/stdc++.h>
using namespace std;

const int inf = (1 << 30);

struct edge {
	int to, f, c;

	edge() = default;

	edge(int nt, int fn, int cn) {
		to = nt;
		f = fn;
		c = cn;
	}
};

int s, t;
vector < vector<int> > g;
vector <edge> lst;
vector <int> d, h, match;
vector <bool> used, cover;

bool bfs(int lock) {
	for (int i = 0; i < (int)d.size(); i++)
		d[i] = inf;

	queue <int> q;
	d[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int i = 0; i < (int)g[v].size(); i++) {
			int to = lst[g[v][i]].to;
			if (d[to] > d[v] + 1 && lst[g[v][i]].c - lst[g[v][i]].f >= lock) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}

	return (d[t] < inf);
}

int dfs(int v, int add, int lock) {
	if (v == t)
		return add;
	for (; h[v] < (int)g[v].size(); h[v]++) {
		int num = g[v][h[v]];
		if (d[v] < d[lst[num].to] && lst[num].c - lst[num].f >= lock) {
			int res = dfs(lst[num].to, min(add, lst[num].c - lst[num].f), lock);
			if (res == 0)
				continue;
			lst[num].f += res;
			lst[num ^ 1].f -= res;
			return res;
		}
	}
	return 0;
}

void dfs0(int v) {
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (lst[g[v][i]].c == 0)
			continue;
		int to = lst[g[v][i]].to;
		used[to] = true;
		if (match[to] != -1 && !used[match[to]])
			dfs0(match[to]);
	}
}

void roadroller(int n, int m) {
	g.clear();
	g.resize(n);
	lst.clear();
	lst.resize(2 * m);
	d.clear();
	d.resize(n);
	used.clear();
	used.resize(n);
	h.clear();
	h.resize(n);
	match.clear();
	match.resize(n, -1);
	cover.clear();
	cover.resize(n);
}

void solve(int nl, int nr) {
	int n, m, a, b, numeric = 0;
	n = 1 + nl + nr + 1;
	cin >> m;

	roadroller(n, m + nl + nr);
	s = 0; t = n - 1;

	for (int i = 0; i < nl; i++) {
		lst[numeric] = edge(i + 1, 0, 1);
		g[s].push_back(numeric++);
		lst[numeric] = edge(s, 0, 0);
		g[i + 1].push_back(numeric++);
	}
	for (int i = 0; i < m; i++) {
		cin >> b >> a;
		b += nl;
		lst[numeric] = edge(b, 0, 1);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0);
		g[b].push_back(numeric++);
	}
	for (int i = 0; i < nr; i++) {
		lst[numeric] = edge(t, 0, 1);
		g[i + 1 + nl].push_back(numeric++);
		lst[numeric] = edge(i + 1 + nl, 0, 0);
		g[t].push_back(numeric++);
	}

	int A = 1;
	while (A) {
		while (bfs(A)) {
			for (int i = 0; i < n; i++) {
				h[i] = 0;
			}
			while (dfs(s, inf, A)) {}
		}
		A >>= 1;
	}
	for (int i = 1; i <= nl; i++) {
		for (int j = 0; j < (int)g[i].size(); j++) {
			int num = g[i][j];
			if (lst[num].f > 0) {
				match[lst[num].to] = i;
				cover[i] = true;
				break;
			}
		}
	}

	for (int i = 0; i < n; i++)
		used[i] = false;

	for (int i = 1; i <= nl; i++) {
		if (!cover[i] && !used[i]) {
			dfs0(i);
		}
	}

	int ans = 0;
	for (int i = 1; i <= nl; i++) {
		if (used[i])
			ans++;
	}

	cout << ans << '\n';
	for (int i = 1; i <= nl; i++) {
		if (used[i])
			cout << i << ' ';
	}
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int nl, nr;
	while (cin >> nl >> nr)
		solve(nr, nl);
    return 0;
}
