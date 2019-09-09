#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

const int inf = (int)2e+9;
const int MAXN = 524300;

int st[2 * MAXN];

inline int get(int l, int r) {
	int resl = inf, resr = inf;
	int nl = n + l - 1, nr = n + r - 1;
	while (nl < nr) {
		if (nl % 2 == 1) {
			resl = min(resl, st[nl]);
			nl++;
		}
		nl /= 2;
		if (nr % 2 == 0) {
			resr = min(st[nr], resr);
			nr--;
		}
		nr /= 2;
	}
	if (nl == nr)
		resl = min(resl, st[nl]);
	return min(resl, resr);
}

inline void change(int pos, int k) {
	st[n + pos - 1] = k;
	pos = (n + pos - 1) >> 1;
	while (pos > 0) {
		st[pos] = min(st[pos << 1], st[(pos << 1) + 1]);
		pos >>= 1;
	}
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int l, r, cc = 1;
	cin >> n;

	while (cc < n)
		cc <<= 1;

	for (int i = 0; i < MAXN; i++)
		st[i] = inf;

	for (int i = cc; i < cc + n; i++)
		cin >> st[i];

	for (int i = cc - 1; i >= 1; i--)
		st[i] = min(st[(i << 1)], st[(i << 1) + 1]);
	n = cc;

	string s;
	while (cin >> s >> l >> r) {
		if (s == "min") {
			cout << get(l, r) << '\n';
		} else {
			change(l, r);
		}
	}

	return 0;
}
