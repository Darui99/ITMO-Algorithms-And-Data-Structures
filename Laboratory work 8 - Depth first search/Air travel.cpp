#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int inf = (int)1e+9 + 7;

int n, mat[MAXN][MAXN], cur_comp;
vector < vector<int> > g, tr_g;
vector <int> color, comp, topsort;

void roadroller() {
	g.clear();
	g.resize(n);
	tr_g.clear();
	tr_g.resize(n);
	color.clear();
	color.resize(n);
	comp.clear();
	comp.resize(n);
	topsort.clear();
	cur_comp = 0;
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
	color[v] = 1;
	comp[v] = cur_comp;
	for (int i = 0; i < (int)tr_g[v].size(); i++) {
		int to = tr_g[v][i];
		if (color[to] == 0)
			tr_dfs(to);
	}
	color[v] = 2;
}

bool check(int x) {
	roadroller();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] <= x) {
				g[i].push_back(j);
				tr_g[j].push_back(i);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	for (int i = 0; i < n; i++)
		color[i] = 0;

	for (int i = n - 1; i >= 0; i--) {
		if (color[topsort[i]] == 0) {
			tr_dfs(topsort[i]);
			cur_comp++;
		}
	}

	if (cur_comp == 1) {
		return true;
	} else {
		return false;
	}
}

int main() {
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cin >> mat[i][j];
	}

	int l = -1, r = inf;
	while (r - l > 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	cout << r;

	return 0;
}
