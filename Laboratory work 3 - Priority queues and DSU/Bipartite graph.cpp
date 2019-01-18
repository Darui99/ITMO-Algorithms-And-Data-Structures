#include <bits/stdc++.h>
using namespace std;

vector <int> p, sz, rev;

int col, shift;

int get(int v) {
	while (p[v] != v) {
		col ^= rev[v];
		v = p[v];
	}
	col ^= rev[v];
	return p[v];
}

void join(int v, int u) {
	col = 0;
	v = get(v);
	int colv = col;

	col = 0;
	u = get(u);
	int colu = col;

	if (v == u)
		return;

	if (sz[v] < sz[u])
		swap(v, u);

	p[u] = v;
	sz[v] += sz[u];
	rev[u] ^= (colv == colu);
}

int main() {
    // freopen("cutting.in", "r", stdin);
    // freopen("cutting.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, a, b, t;
	cin >> n >> m;

	p.resize(n);
	sz.resize(n, 1);
	rev.resize(n);

	for (int i = 0; i < n; i++)
		p[i] = i;

	for (int i = 0; i < m; i++) {
		cin >> t >> a >> b;
		if (t == 0) {
			a = (a + shift) % n;
			b = (b + shift) % n;

			join(a, b);
		} else {
			a = (a + shift) % n;
			b = (b + shift) % n;

			col = 0;
			get(a);
			a = col;

			col = 0;
			get(b);
			b = col;

			if (a == b) {
				cout << "YES\n";
				shift = (shift + 1) % n;
			} else {
				cout << "NO\n";
			}
		}
	}

	return 0;
}
