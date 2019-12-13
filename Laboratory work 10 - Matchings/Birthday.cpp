#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> match, L, R, cover;
vector <bool> used;

bool dfs(int v) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (match[to] == -1 || dfs(match[to])) {
			match[to] = v;
			return true;
		}
	}
	return false;
}

void dfs0(int v) {
	L[v] = true;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		R[to] = true;
		if (match[to] != -1 && !L[match[to]])
			dfs0(match[to]);
	}
}

inline void kuhn(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i);
	}
}

void roadroller(int n, int m) {
	g.clear();
	g.resize(n);
	used.clear();
	used.resize(n);
	cover.clear();
	cover.resize(n);
	L.clear();
	L.resize(n);
	R.clear();
	R.resize(m);
	match.clear();
	match.resize(m, -1);
}

void solve() {
	int n, m, a;
	cin >> n >> m;

	roadroller(n, m);

	vector < vector<bool> > mat(n, vector<bool>(m));

	for (int i = 0; i < n; i++) {
		while (cin >> a) {
			if (a == 0)
				break;
			mat[i][a - 1] = true;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!mat[i][j])
				g[i].push_back(j);
		}
	}

	kuhn(n);

	for (int i = 0; i < m; i++) {
		if (match[i] != -1)
			cover[match[i]] = true;
	}

	for (int i = 0; i < n; i++) {
		if (!cover[i])
			dfs0(i);
	}

	vector <int> ansl, ansr;
	for (int i = 0; i < n; i++) {
		if (L[i])
			ansl.push_back(i);
	}
	for (int i = 0; i < m; i++) {
		if (!R[i])
			ansr.push_back(i);
	}

	cout << (int)ansl.size() + (int)ansr.size() << '\n';
	cout << (int)ansl.size() << " " << (int)ansr.size() << '\n';
	for (int i = 0; i < (int)ansl.size(); i++)
		cout << ansl[i] + 1 << " ";
	cout << '\n';
	for (int i = 0; i < (int)ansr.size(); i++)
		cout << ansr[i] + 1 << " ";
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
	cin >> t;

	while (t--)
		solve();
    return 0;
}
