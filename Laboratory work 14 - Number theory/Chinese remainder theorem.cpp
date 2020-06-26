#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

ll mul(ll a, ll b, ll mod) {
	ll s = a * b;
	ld q = (ld)a / (ld)mod * (ld)b;
	s -= (ll)q * mod;
	s %= mod;
	while (s < 0ll)
		s += mod;
	return s;
}

ll rev(ll a, ll m) {
	if (m == 1ll)
		return 1ll;
	return (1ll - rev(m % a, a) * m) / a + m;
}

inline void solve() {
	ll a, b, p, q;
	cin >> a >> b >> p >> q;
	cout << (a + mul(p, mul(b - a, rev(p, q), p * q), p * q)) % (p * q) << '\n';
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
