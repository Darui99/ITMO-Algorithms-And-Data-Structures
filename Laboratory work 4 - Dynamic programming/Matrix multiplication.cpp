#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll inf = (ll)4e+18;
const int MAXN = 405;

ll dp[MAXN][MAXN];
int par[MAXN][MAXN];

string getAns(int len, int first) {
	string res;
	if (len == 0) {
		res = "A";
	} else {
		int pos = par[len][first];
		res += getAns(pos - first, first);
		res += getAns(first + len - pos - 1, pos + 1);
	}
	if ((int)res.size() > 1)
		res = "(" + res + ")";
	return res;
}

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, l, r;
	cin >> n;

	vector < pair<ll, ll> > arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = inf;
			par[i][j] = -1;
		}
	}

	for (int i = 0; i < n; i++)
		dp[0][i] = 0ll;

	for (int i = 1; i < n; i++) {
		for (int j = 0; j + i < n; j++) {
			l = j; r = i + j;
			for (int k = l; k < r; k++) {
			    ll mult = arr[l].first * arr[k].second * arr[r].second;
				if (dp[i][j] > dp[k - l][l] + dp[r - k - 1][k + 1] + mult) {
					dp[i][j] = dp[k - l][l] + dp[r - k - 1][k + 1] + mult;
					par[i][j] = k;
				}
			}
		}
	}

	cout << getAns(n - 1, 0);
	return 0;
}
