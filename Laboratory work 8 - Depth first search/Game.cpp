#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> color, topsort;

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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b, s;
	cin >> n >> m >> s;

	g.resize(n);
	color.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			dfs(i);
	}

	vector <bool> dp(n, false);
	for (int i = 0; i < n; i++) {
		int v = topsort[i];
		for (int j = 0; j < (int)g[v].size(); j++) {
			int to = g[v][j];
			if (!dp[to])
				dp[v] = true;
		}
	}

	if (dp[s - 1])
		cout << "First player wins";
	else
		cout << "Second player wins";

	return 0;
}
