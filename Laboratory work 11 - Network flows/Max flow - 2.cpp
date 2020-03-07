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
    int n, m, a, b, c, numeric = 0;
	cin >> n >> m;

	g.resize(n);
	lst.resize(2 * m);
	d.resize(n);
	h.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--;
		lst[numeric] = edge(b, 0, c);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0);
		g[b].push_back(numeric++);
	}

	s = 0; t = n - 1;

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

	long long ans = 0ll;
	for (int i = 0; i < (int)g[s].size(); i++)
		ans += (long long)lst[g[s][i]].f;
	cout << ans;
    return 0;
}
