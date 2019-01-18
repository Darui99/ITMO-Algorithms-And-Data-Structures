#include <bits/stdc++.h>
using namespace std;

vector <int> p, sz;

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
}

struct trip {
	string type;
	int a, b;
};

int main() {
    freopen("cutting.in", "r", stdin);
    freopen("cutting.out", "w", stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, q, x;
	cin >> n >> m >> q;

	p.resize(n);
	sz.resize(n, 1);

	for (int i = 0; i < n; i++)
		p[i] = i;

	for (int i = 0; i < m; i++) {
		cin >> x >> x;
	}

	vector <trip> ask(q);
	for (int i = 0; i < q; i++) {
		cin >> ask[i].type >> ask[i].a >> ask[i].b;
		ask[i].a--;
		ask[i].b--;
	}

	vector <string> ans;
	for (int i = q - 1; i >= 0; i--) {
		if (ask[i].type == "cut") {
			join(ask[i].a, ask[i].b);
		} else {
			if (get(ask[i].a) == get(ask[i].b))
				ans.push_back("YES");
			else
				ans.push_back("NO");
		}
	}

	for (int i = (int)ans.size() - 1; i >= 0; i--)
		cout << ans[i] << '\n';

	return 0;
}
