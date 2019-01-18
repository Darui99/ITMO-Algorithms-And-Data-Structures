#include <bits/stdc++.h>
using namespace std;
const int inf = (int)2e+9 + 7;

int main() {
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, a, b, c;
	cin >> n >> m;

	vector < vector< pair<int, int> > > g(n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		a--; b--;
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}

	vector < vector<int> > dp((1 << n), vector<int>(n, inf));
	for (int i = 0; i < n; i++)
		dp[(1 << i)][i] = 0;

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if (!((1 << i) & mask))
				continue;
			if (dp[mask][i] == inf)
				continue;
			for (int j = 0; j < (int)g[i].size(); j++) {
				int to = g[i][j].first, edge = g[i][j].second;
				if ((1 << to) & mask)
					continue;
				dp[mask ^ (1 << to)][to] = min(dp[mask ^ (1 << to)][to], dp[mask][i] + edge);
			}
		}
	}

	int ans = inf;
	for (int i = 0; i < n; i++)
		ans = min(ans, dp[(1 << n) - 1][i]);
	if (ans == inf)
		cout << -1;
	else
		cout << ans;
	return 0;
}
