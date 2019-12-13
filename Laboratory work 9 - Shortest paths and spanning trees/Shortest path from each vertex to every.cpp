#include <bits/stdc++.h>
using namespace std;

const int inf = (int)1e+9 + 7;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;

	vector < vector<int> > g(n);
	for (int i = 0; i < n; i++) {
		g[i].resize(n);
		for (int j = 0; j < n; j++)
			g[i][j] = inf;
		g[i][i] = 0;
	}

	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		g[a - 1][b - 1] = c;
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
			    if (g[i][k] == inf || g[k][j] == inf) {
			        continue;
			    }
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << g[i][j] << " ";
		cout << '\n';
	}

	return 0;
}
