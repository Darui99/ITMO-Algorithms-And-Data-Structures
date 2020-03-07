#include <bits/stdc++.h>
using namespace std;

const int inf = (1 << 17);

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
vector <int> d, h;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, a, b, cl, cr, numeric = 0;
	cin >> n >> m;
	n += 2;

	s = 0; t = n - 1;

	g.resize(n);
	lst.resize(6 * m);
	d.resize(n);
	h.resize(n);

	vector < pair<int, int> > link(m);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> cl >> cr;
		link[i] = make_pair(numeric, numeric + 4);
		// s->to
		lst[numeric] = edge(b, 0, cl);
		g[s].push_back(numeric++);
		lst[numeric] = edge(s, 0, 0);
		g[b].push_back(numeric++);
		// a->t
		lst[numeric] = edge(t, 0, cl);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0);
		g[t].push_back(numeric++);
		// a->b
		lst[numeric] = edge(b, 0, cr - cl);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0);
		g[b].push_back(numeric++);
	}

	int A = inf;
	while (A) {
		while (bfs(A)) {
			for (int i = 0; i < n; i++) {
				h[i] = 0;
			}
			while (dfs(s, inf, A)) {}
		}
		A >>= 1;
	}

	vector <int> ans(m);
	for (int i = 0; i < m; i++) {
		if (lst[link[i].first].f < lst[link[i].first].c) {
			cout << "NO";
			return 0;
		}
		ans[i] = lst[link[i].first].f + lst[link[i].second].f;
	}

	cout << "YES\n";
	for (int i = 0; i < m; i++)
		cout << ans[i] << '\n';
    return 0;
}
