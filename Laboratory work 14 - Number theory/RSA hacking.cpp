#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll bin_pow(ll a, ll n, ll mod) {
	ll res = 1ll, u = a;
	while (n) {
		if (n % 2ll == 1ll)
			res = (res * u) % mod;
		u = (u * u) % mod;
		n /= 2ll;
	}
	return res;
}

ll rev(ll a, ll m) {
	if (m == 1ll)
		return 1ll;
	return (1ll - rev(m % a, a) * m) / a + m;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    ll n, e, c, d = 0ll;
	cin >> n >> e >> c;

	for (ll i = 2ll; i * i <= n; i++) {
		if (n % i == 0ll) {
			d = rev(e, (i - 1ll) * (n / i - 1ll));
			break;
		}
	}
	cout << bin_pow(c, d, n);
	return 0;
}
