#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector <int> p, cnt, read;

bool root(int v) {
	return (p[v] == v);
}

int get(int v) {
	if (v != p[v]) {
		int cur = p[v];
		p[v] = get(p[v]);
		if (!root(cur))
			cnt[v] += cnt[cur];
	}
	return p[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);

	p[v] = u;
}

ll zerg = 0ll, pmod = (ll)1e+6 + 3ll;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, q;
	cin >> n >> q;

	p.resize(n + q);
	cnt.resize(n + q);
	read.resize(n + q);

	for (int i = 0; i < n + q; i++) {
		p[i] = i;
	}

	int type, x, y, numeric = n, ans, cur;
	while (q--) {
		cin >> type;
		if (type == 1) {
			cin >> x;
			x = (x + (int)zerg) % n;
			cnt[get(x)]++;
			zerg = (30ll * zerg + 239ll) % pmod;
		}
		if (type == 2) {
			cin >> x >> y;
			x = (x + (int)zerg) % n;
			y = (y + (int)zerg) % n;
			if (get(x) == get(y)) {
				continue;
			}
			join(x, numeric);
			join(y, numeric);
			numeric++;
			zerg = (13ll * zerg + 11ll) % pmod;
		}
		if (type == 3) {
			cin >> x;
			x = (x + (int)zerg) % n;
			get(x);
			cur = cnt[x];
			if (!root(x))
				cur += cnt[p[x]];
			ans = cur - read[x];
			read[x] = cur;
			cout << ans << '\n';
			zerg = (100500ll * zerg + (ll)ans) % pmod;
		}
	}
	return 0;
}
