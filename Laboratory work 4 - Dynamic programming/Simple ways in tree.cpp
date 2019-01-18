#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector < vector< pair<int, int> > > g;
vector <ll> w, dp;

void set_w(int v, int p) {
	w[v] = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		set_w(to, v);
		w[v] += w[to];
	}
}

void set_dp(int v, int p) {
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		set_dp(to, v);
		dp[v] += dp[to] + w[to];
	}
}

vector <ll> ans;

void dfs(int v, int p, ll summ, ll lsumm, ll sums) {
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first, num = g[v][i].second;
		if (to == p) {
			ans[num] = dp[v] * lsumm + w[v] * summ + w[v] * sums;
			continue;
		}
		ll nsumm = summ + lsumm + w[v] - w[to];
		ll nlsumm = lsumm + w[v] - w[to];
		ll nsums = sums + dp[v] - dp[to] - w[to];
		dfs(to, v, nsumm, nlsumm, nsums);
	}
}

int main() {
    freopen("treedp.in", "r", stdin);
    freopen("treedp.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, a, b;
	cin >> n;

	g.resize(n);
	w.resize(n);
	dp.resize(n);
	ans.resize(n - 1);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
	}

	set_w(0, 0);
	set_dp(0, 0);
	dfs(0, 0, 0ll, 0ll, 0ll);
	for (int i = 0; i < n - 1; i++)
		cout << ans[i] << '\n';
	return 0;
}
