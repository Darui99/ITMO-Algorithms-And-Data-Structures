#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = (ll)1e+9 + 7ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
	ll m;
	cin >> n >> m;

	vector <int> p(n);
	for (int i = 1; i < n; i++)
		cin >> p[i];

	vector <ll> cnt(n);
	cnt[0] = m;

	for (int i = 1; i < n; i++) {
		if (p[i] != 0) {
			cnt[i] = 1ll;
			continue;
		}
		ll cur = m;
		for (int j = p[i - 1]; j; cur -= p[j] == 0, j = p[j - 1]) {}
		cnt[i] = cur - 1ll;
	}

	ll ans = 1ll;
	for (int i = 0; i < n; i++)
		ans = (ans * cnt[i]) % mod;
	cout << ans << endl;
}
