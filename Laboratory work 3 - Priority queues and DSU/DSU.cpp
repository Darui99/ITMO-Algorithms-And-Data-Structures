#include <bits/stdc++.h>
using namespace std;

vector <int> p, sz, maxu, minu;

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
	minu[v] = min(minu[v], minu[u]);
}

int main() {
    freopen("dsu.in", "r", stdin);
    freopen("dsu.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, a, b;
	cin >> n;

	p.resize(n);
	sz.resize(n, 1);
	maxu.resize(n);
	minu.resize(n);

	for (int i = 0; i < n; i++)
		p[i] = maxu[i] = minu[i] = i;

	string type;
	while (cin >> type >> a) {
		a--;
		if (type == "get") {
			a = get(a);
			cout << minu[a] + 1 << " " << maxu[a] + 1 << " " << sz[a] << '\n';
		} else {
			cin >> b;
			b--;
			join(a, b);
		}
	}

	return 0;
}
