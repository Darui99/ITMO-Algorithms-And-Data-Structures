#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = (int)1e+9 + 7;

const int LOGN = 18;
const int MAXN = (int)2e+5 + 5;

int par[LOGN][MAXN], d[LOGN][MAXN];

vector < vector<int> > g;
vector <int> tin, tout;

int timer = 1;
void dfs(int v, int p) {
	par[0][v] = p;
	tin[v] = timer++;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		dfs(to, v);
	}
	tout[v] = timer++;
}

inline bool check_par(int v, int u) {
	return (tin[v] <= tin[u] && tout[u] <= tout[v]);
}

inline int lca(int a, int b) {
	if (check_par(a, b))
		return a;
	if (check_par(b, a))
		return b;

	int now = a;
	for (int i = LOGN - 1; i >= 0; i--) {
		int to = par[i][now];
		if (!check_par(to, a) || !check_par(to, b))
			now = to;
	}
	return par[0][now];
}

inline int get(int v, int p) {
	int res = inf;

	for (int i = LOGN - 1; i >= 0; i--) {
		int to = par[i][v];
		if (check_par(p, to)) {
			res = min(res, d[i][v]);
			v = to;
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, a, b;
	cin >> n;

	g.resize(n);
	tin.resize(n);
	tout.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		g[a - 1].push_back(i + 1);
		d[0][i + 1] = b;
	}

	dfs(0, 0);
	d[0][0] = inf;
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
			d[i][j] = min(d[i - 1][j], d[i - 1][par[i - 1][j]]);
		}
	}

	int q;
	cin >> q;

	while (q--) {
		cin >> a >> b;
		a--; b--;
		int p = lca(a, b);
		cout << min(get(a, p), get(b, p)) << '\n';
	}

	return 0;
}
