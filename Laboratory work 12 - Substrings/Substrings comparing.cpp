#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = (int)1e+5 + 5;
const ll p = (ll)1e+6 + 3ll;
const ll mod = (ll)1e+9 + 7ll;

ll pows[MAXN], h[MAXN];

inline ll get(int l, int r) {
	return (h[r] + mod - h[l - 1] * pows[r - l + 1] % mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    pows[0] = 1ll;
	for (int i = 1; i < MAXN; i++)
		pows[i] = (pows[i - 1] * p) % mod;

	string s;
	cin >> s;

	for (int i = 1; i <= (int)s.size(); i++)
		h[i] = (h[i - 1] * p + (ll)s[i - 1]) % mod;

	int q;
	cin >> q;

	while (q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if (b - a == d - c && get(a, b) == get(c, d)) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}
