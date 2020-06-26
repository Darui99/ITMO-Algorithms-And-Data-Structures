#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

mt19937 rng;

ll mul(ll a, ll b, ll mod) {
	ll s = a * b;
	ld q = (ld)a / (ld)mod * (ld)b;
	s -= (ll)q * mod;
	s %= mod;
	while (s < 0ll)
		s += mod;
	return s;
}

ll bin_pow(ll a, ll n, ll mod) {
	ll res = 1ll, u = a;
	while (n) {
		if (n % 2ll == 1ll)
			res = mul(res, u, mod);
		u = mul(u, u, mod);
		n /= 2ll;
	}
	return res;
}

void solve() {
	ll p;
	cin >> p;

	if (p == 1) {
		cout << "NO\n";
		return;
	}
	if (p == 2ll || p == 3ll) {
		cout << "YES\n";
		return;
	}

	ll mod = p, s = 0ll;
	p--;
	while (p % 2ll == 0ll) {
		s++;
		p /= 2ll;
	}
	ll t = p;

	for (int test = 0; test < 10; test++) {
		ll a = rng() % (mod - 3ll) + 2ll;
		ll x = bin_pow(a, t, mod);
		if (x == 1ll || x == mod - 1ll)
			continue;
		bool flag = false;
		for (ll k = 1ll; k < s; k++) {
			x = mul(x, x, mod);
			if (x == mod - 1ll) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    int t;
	cin >> t;

	while (t--)
		solve();
	return 0;
}
