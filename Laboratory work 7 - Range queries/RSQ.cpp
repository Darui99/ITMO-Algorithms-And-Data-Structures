#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 500005;

ll fen[MAXN];

inline ll pref(int x) {
	ll res = 0ll;
	for (int i = x; i > 0; i = (i & (i + 1)) - 1)
		res += fen[i];
	return res;
}

inline ll get(int l, int r) {
	return pref(r) - pref(l - 1);
}

inline void change(int x, ll k) {
	ll dif = k - get(x, x);
	for (int i = x; i < MAXN; i |= (i + 1))
		fen[i] += dif;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, l, r;
	ll x;
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> x;
		change(i, x);
	}

	string s;
	while (cin >> s) {
		if (s == "sum") {
			cin >> l >> r;
			cout << get(l, r) << '\n';
		} else {
			cin >> l >> x;
			change(l, x);
		}
	}

	return 0;
}
