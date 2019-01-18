#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector < vector<ll> > vvl;

const ll mod = 999999937ll;

vvl mult(const vvl &x, const vvl &y) {
	int a = (int)x.size(), b = (int)x[0].size(), c = (int)y[0].size();
	vvl res(a, vector<ll>(c));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < b; k++)
				res[i][j] = (res[i][j] + x[i][k] * y[k][j] % mod) % mod;
		}
	}
	return res;
}

vvl bin_pow(const vvl &a, ll n) {
	if (n == 0ll) {
		vvl res((int)a.size(), vector<ll>((int)a.size()));
		for (int i = 0; i < (int)a.size(); i++)
			res[i][i] = 1ll;
		return res;
	}
	if (n % 2ll == 0ll) {
		vvl res = bin_pow(a, n / 2ll);
		return mult(res, res);
	} else {
		vvl res = bin_pow(a, n - 1ll);
		return mult(res, a);
	}
}

vvl m;

void solve(ll n) {
	if (n == 0)
		exit(0);

	vvl start = vvl(5, vector<ll>(1, 1ll));
	vvl dp = mult(bin_pow(m, n - 1ll), start);

	ll ans = 0ll;
	for (int i = 0; i < 5; i++)
		ans = (ans + dp[i][0]) % mod;

	cout << ans << '\n';
}

int main() {
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	m = vvl(5, vector<ll>(5, 1ll));
	m[2][3] = m[2][4] = m[4][3] = m[4][4] = 0ll;

	ll n;

	while (cin >> n)
		solve(n);
	return 0;
}
