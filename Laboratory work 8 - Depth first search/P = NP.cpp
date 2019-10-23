#include <bits/stdc++.h>
using namespace std;

int n, m, cur_comp;
vector < vector<int> > g, tr_g;
vector <int> color, comp, topsort;

inline void add_edge(int a, int b) {
	g[a].push_back(b);
	tr_g[b].push_back(a);
}

void dfs(int v) {
	color[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
	topsort.push_back(v);
}

void tr_dfs(int v) {
	comp[v] = cur_comp;
	color[v] = 1;
	for (int i = 0; i < (int)tr_g[v].size(); i++) {
		int to = tr_g[v][i];
		if (color[to] == 0)
			tr_dfs(to);
	}
	color[v] = 2;
}

int main() {
    freopen("cnf.in", "r", stdin);
    freopen("cnf.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b, c, adda, addb, addc;
	cin >> n >> m;

	g.resize(2 * n);
	tr_g.resize(2 * n);
	color.resize(2 * n);
	comp.resize(2 * n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		adda = 0; addb = 0; addc = 0;
		if (a < 0) {
			a = -a;
			adda = 1;
		}
		if (b < 0) {
			b = -b;
			addb = 1;
		}
		if (c < 0) {
			c = -c;
			addc = 1;
		}
		a--; b--; c--;
		add_edge(2 * a + !adda, 2 * b + addb);
		add_edge(2 * b + !addb, 2 * a + adda);
		add_edge(2 * a + !adda, 2 * c + addc);
		add_edge(2 * c + !addc, 2 * a + adda);
		add_edge(2 * b + !addb, 2 * c + addc);
		add_edge(2 * c + !addc, 2 * b + addb);
	}

	for (int i = 0; i < 2 * n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	for (int i = 0; i < 2 * n; i++)
		color[i] = 0;

	for (int i = 2 * n - 1; i >= 0; i--) {
		if (color[topsort[i]] == 0) {
			tr_dfs(topsort[i]);
			cur_comp++;
		}
	}

	for (int i = 0; i < n; i++) {
		if (comp[2 * i] == comp[2 * i + 1]) {
			cout << "NO";
			return 0;
		}
	}

	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		if (comp[2 * i] > comp[2 * i + 1]) {
			cout << i + 1 << " ";
		} else {
			cout << -(i + 1) << " ";
		}
	}

	return 0;
}
