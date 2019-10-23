#include <bits/stdc++.h>
using namespace std;

vector < vector<int> > g;
vector <int> color, comp;

int cur_comp = 1;

void dfs(int v) {
	color[v] = 1;
	comp[v] = cur_comp;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i];
		if (color[to] == 0)
			dfs(to);
	}
	color[v] = 2;
}

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, a, b;
	cin >> n >> m;

	g.resize(n);
	color.resize(n);
	comp.resize(n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
		g[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < n; i++) {
		if (color[i] == 0) {
			dfs(i);
			cur_comp++;
		}
	}
	cout << cur_comp - 1 << '\n';
	for (int i = 0; i < n; i++)
	    cout << comp[i] << " ";

	return 0;
}
