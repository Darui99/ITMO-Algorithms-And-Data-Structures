#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = (ll)9e+18;
const int MAXN = 2005;

ll arr[MAXN], h[MAXN];
ll dp[MAXN][MAXN];
int par[MAXN][MAXN];

ll get(int l, int r) {
	if (l > r)
		return 0ll;
	return h[r] - h[l - 1];
}

string ans;
void getAns(int l, int r) {
	if (l == r) {
		cout << ans << '\n';
		return;
	}
	int pos = par[r - l + 1][l];
	ans.push_back('0');
	getAns(l, pos);
	ans.pop_back();
	ans.push_back('1');
	getAns(pos + 1, r);
	ans.pop_back();
}

int main() {
    freopen("optimalcode.in", "r", stdin);
    freopen("optimalcode.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		h[i] = h[i - 1] + arr[i];
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = inf;
			par[i][j] = -1;
		}
	}

	for (int i = 1; i <= n; i++) {
		dp[1][i] = 0ll;
		par[1][i] = i;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 1; j + i - 1 <= n; j++) {
			int l = j, r = i + j - 1;
			for (int k = par[i - 1][l]; k <= par[i - 1][l + 1]; k++) {
				if (dp[i][j] > dp[k - l + 1][l] + dp[r - k][k + 1] + get(l, r)) {
					dp[i][j] = dp[k - l + 1][l] + dp[r - k][k + 1] + get(l, r);
					par[i][j] = k;
				}
			}
		}
	}

	cout << dp[n][1] << '\n';
	getAns(1, n);
	return 0;
}
