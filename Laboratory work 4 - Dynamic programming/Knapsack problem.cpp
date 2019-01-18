#include <bits/stdc++.h>
using namespace std;
const int inf = (int)2e+9;

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, S;
	cin >> n >> S;

	vector <int> w(n), c(n);
	for (int i = 0; i < n; i++)
		cin >> w[i];
	for (int i = 0; i < n; i++)
		cin >> c[i];

	vector < vector<int> > dp(n + 1, vector <int>(S + 1, -inf)), par(n + 1, vector<int>(S + 1, -1));

	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= S; j++) {
			dp[i][j] = dp[i - 1][j];
			par[i][j] = j;
			if (j - w[i - 1] < 0 || dp[i - 1][j - w[i - 1]] == -inf)
				continue;
			if (dp[i][j] < dp[i - 1][j - w[i - 1]] + c[i - 1]) {
				dp[i][j] = dp[i - 1][j - w[i - 1]] + c[i - 1];
				par[i][j] = j - w[i - 1];
			}
		}
	}

	int ans = -inf, ansi = -1;
	for (int i = 0; i <= S; i++) {
		if (dp[n][i] > ans) {
			ans = dp[n][i];
			ansi = i;
		}
	}

	vector <int> path;
	int cur = ansi;
	for (int i = n; i > 0; i--) {
		int prev = par[i][cur];
		if (prev < cur) {
			path.push_back(i);
			cur = prev;
		}
	}

	cout << (int)path.size() << endl;
	for (int i = (int)path.size() - 1; i >= 0; i--)
		cout << path[i] << " ";
	return 0;
}
