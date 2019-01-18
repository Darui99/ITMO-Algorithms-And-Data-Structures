#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 16;
ll g[MAXN][MAXN];
ll dp[(1ll << MAXN)][MAXN];

ll gcd(ll a, ll b) {
	while (b)
		b ^= a ^= b ^= a %= b;
	return a;
}

int main() {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll n, m, k;
	cin >> n >> m >> k;
	m--;

	vector <ll> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			g[i][j] = gcd(arr[i], arr[j]);
		dp[(1ll << i)][i] = 1ll;
	}

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if (dp[mask][i] == 0 || !((1 << i) & mask))
				continue;
			for (int to = 0; to < n; to++) {
				if (g[i][to] < k || ((1 << to) & mask))
					continue;
				dp[mask ^ (1 << to)][to] += dp[mask][i];
			}
		}
	}

	vector <int> path;
	int curMask = 0, all = (1 << n) - 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if ((1 << j) & curMask)
				continue;
			if (!path.empty() && g[path.back()][j] < k)
				continue;
			if (dp[all ^ curMask][j] <= m) {
				m -= dp[all ^ curMask][j];
			} else {
				curMask ^= (1 << j);
				path.push_back(j);
				break;
			}
		}
	}

	if (m > 0 || (int)path.size() != n) {
		cout << -1;
	} else {
		for (int i = 0; i < n; i++)
			cout << arr[path[i]] << " ";
	}
	return 0;
}
