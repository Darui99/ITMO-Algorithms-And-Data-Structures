#include <bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e+4 + 5;
bitset <MAXN> dp[MAXN], pref[MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    string t, a;
	cin >> t >> a;

	int n = (int)t.size(), m = (int)a.size();

	dp[0][0] = true;
	pref[0][0] = true;
	for (int i = 0; i <= m; i++)
		pref[0][i] = true;
	for (int i = 1; i <= n; i++) {
		if (t[i - 1] == '*') {
			dp[i][0] = true;
			pref[i][0] = true;
		} else {
			break;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (t[i - 1] == '?') {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				if (t[i - 1] != '*') {
					if (t[i - 1] == a[j - 1])
						dp[i][j] = dp[i - 1][j - 1];
				} else {
					dp[i][j] = pref[i - 1][j];
				}
			}
			pref[i][j] = dp[i][j] | pref[i][j - 1];
		}
	}

	if (dp[n][m])
		cout << "YES";
	else
		cout << "NO";
	return 0;
}
