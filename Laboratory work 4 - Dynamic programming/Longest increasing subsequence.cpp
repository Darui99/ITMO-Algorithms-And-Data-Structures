#include <bits/stdc++.h>
using namespace std;
const int inf = (int)2e+9;

int main() {
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector <int> arr(n), dp(n, inf), ind(n), par(n, -1);
	int ans = 0, ansi = -1;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		int p = (int)(lower_bound(dp.begin(), dp.end(), arr[i]) - dp.begin());
		dp[p] = arr[i];
		if (p > 0)
			par[i] = ind[p - 1];
		ind[p] = i;
		if (p + 1 > ans) {
			ans = p + 1;
			ansi = i;
		}
	}

	cout << ans << endl;
	vector <int> path;

	int cur = ansi;
	while (true) {
		path.push_back(arr[cur]);
		cur = par[cur];
		if (cur == -1)
			break;
	}

	for (int i = ans - 1; i >= 0; i--)
		cout << path[i] << " ";
	return 0;
}
