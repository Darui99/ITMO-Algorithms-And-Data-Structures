#include <bits/stdc++.h>
using namespace std;

vector <int> p[2], sz[2];

int get(int t, int v) {
	if (v != p[t][v])
		p[t][v] = get(t, p[t][v]);
	return p[t][v];
}

void join(int t, int v, int u) {
	v = get(t, v);
	u = get(t, u);

	if (v == u)
		return;

	p[t][v] = u;
	sz[t][u] += sz[t][v];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, q;
	cin >> n >> q;

	p[0].resize(n);
	sz[0].resize(n, 1);
	for (int i = 0; i < n; i++)
		p[0][i] = i;

	p[1].resize(2 * n);
	sz[1].resize(2 * n, 1);
	for (int i = 0; i < 2 * n; i++)
		p[1][i] = i;

	for (int i = 1; i < 2 * n - 2; i += 2)
		join(1, i, i + 1);

	int type, x, y, cur, next;
	while (q--) {
		cin >> type >> x >> y;
		x--; y--;
		if (type == 1) {
			join(0, x, y);
		}
		if (type == 2) {
		    if (x == y) {
		        continue;
		    }
			cur = x;
			while (true) {
				next = get(1, 2 * cur + 1) / 2;
				join(0, cur, next);
				join(1, 2 * cur, 2 * cur + 1);
				if (next >= y)
					break;
				cur = next;
			}
		}
		if (type == 3) {
			x = get(0, x);
			y = get(0, y);
			if (x == y)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}

	return 0;
}
