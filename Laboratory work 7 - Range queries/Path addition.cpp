#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

const int LOGN = 20;
const int MAXN = 1048580;

int par[LOGN][MAXN];

ll st[2 * MAXN], arr[MAXN];

inline ll get(int l, int r) {
	ll resl = 0ll, resr = 0ll;
	int nl = n + l - 1, nr = n + r - 1;
	while (nl < nr) {
		if (nl % 2 == 1) {
			resl += st[nl];
			nl++;
		}
		nl /= 2;
		if (nr % 2 == 0) {
			resr += st[nr];
			nr--;
		}
		nr /= 2;
	}
	if (nl == nr)
		resl += st[nl];
	return resl + resr;
}

inline void change(int pos, ll k) {
	st[n + pos - 1] += k;
	pos = (n + pos - 1) >> 1;
	while (pos > 0) {
		st[pos] = st[pos << 1] + st[(pos << 1) + 1];
		pos >>= 1;
	}
}

vector < vector<int> > g;
vector <int> tin, tout;

int timer = 1;

void dfs(int v, int p) {
	par[0][v] = p;
	tin[v] = timer++;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (to == p)
			continue;
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

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int cc = 1, a, b, q;
	cin >> n;

	g.resize(n);
	tin.resize(n);
	tout.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(0, 0);

	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < n; j++)
			par[i][j] = par[i - 1][par[i - 1][j]];
	}
	n <<= 1;
	while (cc < n)
		cc <<= 1;
	n = cc;

	cin >> q;
	char type;
	ll k;
	while (q--) {
		cin >> type;
		if (type == '+') {
			cin >> a >> b >> k;
			a--; b--;
			cc = lca(a, b);
			change(tin[a], k);
			change(tin[b], k);
			change(tin[cc], -2ll * k);
			arr[cc] += k;
		} else {
			cin >> a;
			a--;
			cout << get(tin[a], tout[a]) + arr[a] << '\n';
		}
	}

	return 0;
}
