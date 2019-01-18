#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll mod = (ll)1e+9;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <int> arr(n);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	vector < vector<ll> > dp(n, vector<ll>(n));
	for (int i = 0; i < n; i++)
		dp[0][i] = 1ll;
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] == arr[i + 1])
			dp[1][i] = 3ll;
		else
			dp[1][i] = 2ll;
	}

	for (int i = 2; i < n; i++) {
		for (int j = 0; j + i < n; j++) {
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j + 1] - dp[i - 2][j + 1] + mod) % mod;
			if (arr[j] == arr[i + j])
				dp[i][j] = (dp[i][j] + dp[i - 2][j + 1] + 1ll) % mod;
		}
	}

	cout << dp[n - 1][0];
	return 0;
}
