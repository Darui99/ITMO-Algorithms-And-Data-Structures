#include <bits/stdc++.h>
using namespace std;

vector <int> p, sz, maxu;

int get(int v) {
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

void join(int v, int u) {
	v = get(v);
	u = get(u);

	if (v == u)
		return;

	if (sz[v] < sz[u])
		swap(v, u);

	p[u] = v;
	sz[v] += sz[u];
	maxu[v] = max(maxu[v], maxu[u]);
}

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, x;
	cin >> n;

	p.resize(2 * n + 2);
	sz.resize(2 * n + 2, 1);
	maxu.resize(2 * n + 2);

	for (int i = 0; i < 2 * n + 2; i++)
		p[i] = maxu[i] = i;

	for (int i = 1; i < 2 * n; i += 2)
		join(i, i + 1);

	for (int i = 0; i < n; i++) {
		cin >> x;
		x--;

		int cur = maxu[get(2 * x + 1)];
		if (cur == 2 * n + 1)
			cur = maxu[get(1)];
		cur = cur / 2;
		cout << cur << " ";
		join(2 * cur, 2 * cur + 1);
	}

	return 0;
}
