#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
int w[MAXN], pare[MAXN], parv[MAXN];
vector < vector < vector < pair<int, int> > > > par;
vector < vector < vector <int> > > dp;

vector < vector< pair<int, int> > > g;

void dfs(int v, int p) {
	parv[v] = p;
	w[v] = 1;

	dp[v].resize((int)g[v].size() - (v != 0) + 1);
	par[v].resize((int)g[v].size() - (v != 0) + 1);

	dp[v][0].resize(2, MAXN);
	par[v][0].resize(2, make_pair(-1, -1));
	dp[v][0][1] = (int)g[v].size() - (v != 0);
	int ptr = 1;
	for (int i = 0; i < (int)g[v].size(); i++) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		pare[to] = g[v][i].second;
		dfs(to, v);
		w[v] += w[to];
		par[v][ptr].resize(w[v] + 1, make_pair(-1, -1));
		dp[v][ptr].resize(w[v] + 1, MAXN);

		for (int sum = w[v]; sum >= 0; sum--) {
			if ((int)dp[v][ptr - 1].size() - 1 >= sum) {
				dp[v][ptr][sum] = dp[v][ptr - 1][sum];
				par[v][ptr][sum] = make_pair(v, sum);
			}
			for (int x = 0; x <= min(w[to], sum); x++) {
				int y = sum - x;
				if ((int)dp[v][ptr - 1].size() - 1 < y)
					continue;
				if (dp[v][ptr][sum] > dp[v][ptr - 1][y] + dp[to].back()[x] - 1) {
					dp[v][ptr][sum] = dp[v][ptr - 1][y] + dp[to].back()[x] - 1;
					par[v][ptr][sum] = make_pair(to, x);
				}
			}
		}
		ptr++;
	}
}

vector <int> path;

void getAns(int v, int p, int sum) {
	int ptr = (int)g[v].size() - (v != 0);
	pair <int, int> cur = par[v][ptr][sum];
	for (int i = (int)g[v].size() - 1; i >= 0; i--) {
		int to = g[v][i].first;
		if (to == p)
			continue;
		if (to == cur.first) {
			getAns(to, v, cur.second);
			sum -= cur.second;
		} else {
			path.push_back(pare[to]);
		}
		ptr--;
		cur = par[v][ptr][sum];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, p, a, b;
	cin >> n >> p;

	g.resize(n);
	par.resize(n);
	dp.resize(n);

	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		a--; b--;
		g[a].push_back(make_pair(b, i));
		g[b].push_back(make_pair(a, i));
	}

	dfs(0, 0);

	int ans = MAXN, ansi = -1;
	for (int i = 0; i < n; i++) {
		if ((int)dp[i].back().size() - 1 >= p && ans > dp[i].back()[p] + (i != 0)) {
			ans = dp[i].back()[p] + (i != 0);
			ansi = i;
		}
	}

	if (ansi != 0)
		path.push_back(pare[ansi]);
	getAns(ansi, parv[ansi], p);

	cout << ans << endl;
	sort(path.begin(), path.end());

	for (int i = 0; i < ans; i++)
		cout << path[i] + 1 << " ";
	return 0;
}
