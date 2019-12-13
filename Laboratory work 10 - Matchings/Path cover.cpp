#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> match;
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

inline int kuhn(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = false;
		dfs(i);
	}
	int res = 0;
	for (int i = 0; i < m; i++)
		res += (match[i] != -1);
	return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k, a, b;
	cin >> n >> k;

	g.resize(n);
	used.resize(n);
	match.resize(n, -1);

	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
	}

	cout << n - kuhn(n, n);
    return 0;
}
