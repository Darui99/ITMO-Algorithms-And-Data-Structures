#include <bits/stdc++.h>
using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

vector < vector<int> > g;
vector <int> p, color;

void dfs(int v, int par) {
	p[v] = par;
	color[v] = 1;
	forn(i, (int)g[v].size()) {
		int to = g[v][i];
		if (color[to] == 1) {
			cout << "YES\n";
			int cur = v;
			vector <int> ans;
			while (true) {
				ans.push_back(cur + 1);
				if (cur == to)
					break;
				cur = p[cur];
			}
			for (int i = (int)ans.size() - 1; i >= 0; i--)
				cout << ans[i] << " ";
			exit(0);
		}
		if (color[to] == 0)
			dfs(to, v);
	}
	color[v] = 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;

	g.resize(n);
	color.resize(n);
	p.resize(n);

	forn(i, m) {
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0)
			dfs(i, i);
	}

	cout << "NO";

	return 0;
}
