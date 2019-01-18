#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ask(ll x) {
	cout << "? " << x << endl;
	ll  res;
	cin >> res;
	return res;
}

int main() {
    // freopen("buckets.in", "r", stdin);
    // freopen("buckets.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n = (ll)1e+18, m, x;
	cin >> x >> m;

	ll primero = ask(1ll), shift = primero - 1ll;
	x = x - shift;
	if (x <= 0ll)
		x += n;

	ll l = max(1ll, x - m), r, dif = n - x;
	r = x - max(0ll, m - dif);

	while (l <= r) {
		ll mid = (l + r) / 2ll;
		ll cur = ask(mid) - shift;
		if (cur <= 0ll)
			cur += n;

		if (cur == x) {
			cout << "! " << mid << endl;
			return 0;
		}

		if (cur <= x)
			l = mid + 1;
		else
			r = mid - 1ll;
	}

	cout << "! " << -1 << endl;
    return 0;
}
