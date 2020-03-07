#include <bits/stdc++.h>
using namespace std;

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
vector <int> d, h, e;
vector <bool> blocked;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, l, a, b, c, numeric = 0;
	cin >> n >> m >> l;

	g.resize(n);
	d.resize(n);
	lst.resize(2 * m);
	e.resize(n);
	blocked.resize(n);
	h.resize(n);

	int s = -1, t = -1;
	for (int i = 0; i < n; i++) {
		cin >> d[i];
		if (d[i] == 1)
			s = i;
		if (d[i] == l)
			t = i;
	}

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--;
		lst[numeric] = edge(b, 0, c);
		g[a].push_back(numeric++);
		lst[numeric] = edge(a, 0, 0);
		g[b].push_back(numeric++);
	}

	vector < pair<int, int> > ord(n);
	for (int i = 0; i < n; i++)
		ord[i] = make_pair(d[i], i);
	sort(ord.begin(), ord.end());

	for (; h[s] < (int)g[s].size(); h[s]++) {
		int num = g[s][h[s]];
		e[lst[num].to] = lst[num].c;
		lst[num].f += lst[num].c;
		lst[num ^ 1].f -= lst[num].c;
	}
	while (true) {
		bool any = false;
		for (int i = 1; i < n; i++) {
			int v = ord[i].second;
			if (blocked[v])
				continue;
			for (; h[v] < (int)g[v].size(); h[v]++) {
				int num = g[v][h[v]];
				if (d[v] >= d[lst[num].to] || blocked[lst[num].to])
					continue;
				int add = min(e[v], lst[num].c - lst[num].f);
				e[v] -= add;
				e[lst[num].to] += add;
				lst[num].f += add;
				lst[num ^ 1].f -= add;
				if (e[v] == 0)
					break;
			}
			if (e[v] > 0 && v != t && !blocked[v]) {
				any = true;
				blocked[v] = true;
				h[v] = 0;
			}
		}

		for (int i = n - 2; i >= 0; i--) {
			int v = ord[i].second;
			if (!blocked[v])
				continue;
			for (; h[v] < (int)g[v].size(); h[v]++) {
				int num = g[v][h[v]];
				if (d[v] < d[lst[num].to])
					continue;
				int add = max(0, min(e[v], -lst[num].f));
				e[lst[num].to] += add;
				e[v] -= add;
				lst[num].f += add;
				lst[num ^ 1].f -= add;
				if (e[v] == 0)
					break;
			}
		}
		if (!any)
			break;
	}
	for (int i = 0; i < (int)lst.size(); i += 2)
		cout << lst[i].f << '\n';
    return 0;
}
