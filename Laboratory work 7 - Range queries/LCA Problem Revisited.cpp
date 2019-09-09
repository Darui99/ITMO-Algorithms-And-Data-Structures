#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int LOGN = 18;
const int MAXN = (int)2e+5 + 5;

int d[LOGN][MAXN], ver[LOGN][MAXN], pows[MAXN], pos[MAXN];

vector < vector<int> > g;

int timer = 0;

void dfs(int v, int h) {
	d[0][timer] = h;
	ver[0][timer] = v;
	pos[v] = timer++;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		dfs(to, h + 1);
		d[0][timer] = h;
		ver[0][timer++] = v;
	}
}

inline int get(int l, int r) {
	int cur_pow = pows[r - l + 1], cur_len = (1 << cur_pow);
	if (d[cur_pow][l] < d[cur_pow][r - cur_len + 1]) {
		return ver[cur_pow][l];
	} else {
		return ver[cur_pow][r - cur_len + 1];
	}
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for (int i = 2; i < MAXN; i++)
		pows[i] = pows[i / 2] + 1;

	for (int i = 0; i < LOGN; i++) {
		for (int j = 0; j < MAXN; j++) {
			d[i][j] = MAXN;
			ver[i][j] = -1;
		}
	}

	int n, m, o;
	cin >> n >> m;
	m--;

	g.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> o;
		g[o].push_back(i + 1);
	}

	dfs(0, 0);

	int p = 1;
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j + p < MAXN; j++) {
			if (d[i - 1][j] < d[i - 1][j + p]) {
				d[i][j] = d[i - 1][j];
				ver[i][j] = ver[i - 1][j];
			} else {
				d[i][j] = d[i - 1][j + p];
				ver[i][j] = ver[i - 1][j + p];
			}
		}
		p *= 2;
	}

	ll x, y, z, sum = 0ll;
	int al, ar, na, v, u, res;

	cin >> al >> ar >> x >> y >> z;

	v = al; u = ar;
	res = get(min(pos[v], pos[u]), max(pos[v], pos[u]));
	sum += (ll)res;

	while (m--) {
		na = (int)((x * (ll)al + y * (ll)ar + z) % (ll)n);
		al = ar;
		ar = na;
		na = (int)((x * (ll)al + y * (ll)ar + z) % (ll)n);
		al = ar;
		ar = na;
		v = (al + res) % n;
		u = ar;
		res = get(min(pos[v], pos[u]), max(pos[v], pos[u]));
		sum += (ll)res;
	}

	cout << sum;

	return 0;
}
