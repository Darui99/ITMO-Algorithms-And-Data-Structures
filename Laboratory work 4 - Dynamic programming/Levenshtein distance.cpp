#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string a, b;
	cin >> a >> b;

	int n = (int)a.size(), m = (int)b.size();
	vector < vector<int> > dp(n + 1, vector<int>(m + 1, (int)2e+9));

	dp[0][0] = 0;
	for (int i = 1; i <= n; i++)
		dp[i][0] = i;
	for (int i = 1; i <= m; i++)
		dp[0][i] = i;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
			dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
			if (a[i - 1] == b[j - 1])
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
			else
				dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
		}
	}
	cout << dp[n][m];
	return 0;
}
