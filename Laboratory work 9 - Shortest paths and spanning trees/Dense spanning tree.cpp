#include <bits/stdc++.h>
using namespace std;

const int inf = (int)2e+9 + 7;

vector <int> p, sz;

int get(int v) {
	if (p[v] != v)
		p[v] = get(p[v]);
	return p[v];
}

int comp;

void join(int v, int u) {
	v = get(v);
	u = get(u);
	if (v == u)
		return;
	comp--;
	if (sz[v] < sz[u])
		swap(v, u);
	p[u] = v;
	sz[v] += sz[u];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m;
	cin >> n >> m;
	if (n == 1) {
		cout << "YES\n0";
		return 0;
	}
	p.resize(n);
	sz.resize(n);

	vector < vector<int> > edge(m);
	for (int i = 0; i < m; i++) {
		edge[i].resize(3);
		cin >> edge[i][1] >> edge[i][2] >> edge[i][0];
		edge[i][1]--; edge[i][2]--;
	}

	int ans = inf, prev = 0;
	sort(edge.begin(), edge.end());

	for (int i = 1; i < m; i++) {
		if (edge[i - 1][0] != edge[i][0]) {
			random_shuffle(edge.begin() + prev, edge.begin() + i);
			prev = i;
		}
	}
	random_shuffle(edge.begin() + prev, edge.end());

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			p[j] = j;
			sz[j] = 1;
		}
		comp = n;
		for (int j = i; j < m; j++) {
			if (comp == 1) {
				ans = min(ans, edge[j][0] - edge[i][0]);
				break;
			}
			join(edge[j][1], edge[j][2]);
			if (comp == 1) {
				ans = min(ans, edge[j][0] - edge[i][0]);
				break;
			}
		}
	}

	if (ans == inf) {
		cout << "NO";
	} else {
		cout << "YES\n" << ans;
	}

	return 0;
}
