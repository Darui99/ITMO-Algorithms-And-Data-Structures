#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = (int)1e+5 + 5;

ll dp[MAXN][2];
vector < vector< pair<int, ll> > > g;

void dfs(int v, int p) {
	ll sum = 0ll;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		dfs(to, v);
		sum += max(dp[to][0], dp[to][1]);
	}
	dp[v][0] = sum;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		ll edge = g[v][i].second;
		if (to == p)
			continue;
		dp[v][1] = max(dp[v][1], sum - max(dp[to][0], dp[to][1]) + dp[to][0] + edge);
	}
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	g.resize(n);

	int a, b;
	ll c;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b >> c;
		a--; b--;
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}

	dfs(0, 0);
	cout << max(dp[0][0], dp[0][1]);
	return 0;
}
