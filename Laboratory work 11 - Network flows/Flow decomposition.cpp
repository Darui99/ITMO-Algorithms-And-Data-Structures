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

vector < pair<int, vector<int> > > ans;
vector <int> color;
vector < pair<int, int> > par;

bool go(int v, pair<int, int> p) {
	color[v] = 1;
	par[v] = p;
	if (v == t) {
		int add = inf;
		pair <int, int> cur = make_pair(t, -1);
		vector <int> path;
		while (true) {
			color[cur.first] = 0;
			if (cur.second != -1) {
				path.push_back(cur.second);
				add = min(add, lst[cur.second].f);
			}
			if (par[cur.first].first == -1)
				break;
			cur = par[cur.first];
		}
		for (int i = 0; i < (int)path.size(); i++) {
			lst[path[i]].f -= add;
			lst[path[i] ^ 1].f += add;
		}
		reverse(path.begin(), path.end());
		ans.push_back(make_pair(add, path));
		return true;
	}
	for (int i = 0; i < (int)g[v].size(); i++) {
		int num = g[v][i];
		if (num % 2 == 1 || lst[num].f == 0)
			continue;
		if (color[lst[num].to] == 0) {
			return go(lst[num].to, make_pair(v, num));
		}
	}
	return false;
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
	color.resize(n);
	par.resize(n);

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

	while (go(s, make_pair(-1, -1))) {}

	cout << (int)ans.size() << '\n';
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i].first << " " << (int)ans[i].second.size() << " ";
		for (int j = 0; j < (int)ans[i].second.size(); j++)
			cout << ans[i].second[j] / 2 + 1 << " ";
		cout << '\n';
	}
    return 0;
}
